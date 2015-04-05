/*
 * Copyright (C) 2014-2015 Wilds
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/mman.h>
#include <getopt.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>

#include "avrspi_commands.h"
#include "routines.h"
#include "udpconfig.h"

#define CFG_PATH "/etc/avrminicopter/"

struct udp_config config;
#define MIN 0
#define MAX 1
#define YAW 0
#define PITCH 1
#define ROLL 2

int ret;
int err = 0;
int stop = 0;

int avr_s[256];

int trim[3] = {0, 0, 0}; //in degrees * 1000
int mode = 0;
int rec_setting = 0;

int alt_hold = 0;
int throttle_hold = 0;
int throttle_target = 0;

int sock = 0;
char sock_path[256] = "/dev/avrspi";
struct sockaddr_un address;
int addrlen;

int ssock;
struct sockaddr_in saddress;
int sportno = 1032;
char data[256];
int background = 0;
char pidfile[256] = "\0";
int verbose = 0;

int yprt[4] = {0, 0, 0, 0};

long dt_ms = 0;
static struct timespec ts, t1, t2, t3, *dt, lastPacketTime;

int recording = 0;

int logmode = 0;

#define CAMERA_CMD "/usr/local/bin/camera.sh"

#define FIXED_HEIGHT 240

int sendMsg(int t, int v) {
    static unsigned char buf[4];
    static struct local_msg m;
    m.c = 0;
    m.t = t;
    m.v = v;
    pack_lm(buf, &m);
    if (write(sock, buf, 4) < 0) {
        perror("writing");
        return -1;
    }
    return 0;
}

char** str_split(char* a_str, const char a_delim) {
    char** result = 0;
    size_t count = 0;
    char* tmp = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = (char**) malloc(sizeof (char*) * count);

    if (result) {
        size_t idx = 0;
        char* token = strtok(a_str, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

const char * handle_packet(char * data, sockaddr_in remoteAddr) {

    char** tokens = str_split(data, ' ');
    if (!tokens)
        return "KO 0";

    char * resp = (char*) malloc(sizeof (char) * 255);
    memset(resp, '\0', 255);

    clock_gettime(CLOCK_REALTIME, &lastPacketTime);

    if (strcmp(tokens[0], "hello") == 0) {

    } else if (strcmp(tokens[0], "stream") == 0) {
        char *ip = inet_ntoa(remoteAddr.sin_addr);

        // handle aspect ratio
        float aspectratio = atof(tokens[4]) / atof(tokens[5]);
        int height = FIXED_HEIGHT;
        int width = (aspectratio * height);

        char cmd[256];
        memset(cmd, '\0', 256);
        sprintf(cmd, "%s %s %s %s %s %i %i &", CAMERA_CMD, tokens[0], tokens[2], ip, tokens[3], width, height);
        if (verbose) printf("Executing: %s\n", cmd);
        ret = system(cmd);

        if (ret != 0) {
            snprintf(resp, 255, "KO %s %s", tokens[1], tokens[2]);
            return resp;
        } else {
            snprintf(resp, 255, "OK %s %s", tokens[1], tokens[2]);
            return resp;
        }
    } else if (strcmp(tokens[0], "rcinput") == 0) {
        yprt[0] = config.rec_ypr[YAW] * atoi(tokens[3]) / 100;
        yprt[1] = config.rec_ypr[PITCH] * atoi(tokens[4]) / 100;
        yprt[2] = config.rec_ypr[ROLL] * atoi(tokens[5]) / 100;
        yprt[3] = config.throttle[MIN] + atoi(tokens[2]) * (config.throttle[MAX] - config.throttle[MIN]) / 100;

        /*
        dt = TimeSpecDiff(&lastPacketTime, &t3);
        dt_ms = dt->tv_sec * 1000 + dt->tv_nsec / 1000000;
        if (dt_ms < 50) {
            //mssleep(50 - dt_ms);
            return ""; //do not flood AVR with data - will cause only problems; each loop sends 4 msg; 50ms should be enough for AVR to consume them
        }
        t3 = lastPacketTime;

        sendMsg(COMMAND_SET_YAW, yprt[0]);
        sendMsg(COMMAND_SET_PITCH, yprt[1]);
        sendMsg(COMMAND_SET_ROLL, yprt[2]);
        sendMsg(COMMAND_SET_THROTTLE, yprt[3]);
        */

        return ""; //controller not wait respose for rcinput command

    } else if (strcmp(tokens[0], "heartbeat") == 0) {

    } else if (strcmp(tokens[0], "flymode") == 0) {
        if (strcmp(tokens[2], "stable"))
            sendMsg(COMMAND_SET_FLY_MODE, PARAMETER_SET_FLY_MODE_STABLE);
        else if (strcmp(tokens[2], "acro"))
            sendMsg(COMMAND_SET_FLY_MODE, PARAMETER_SET_FLY_MODE_ACRO);
        else
            sendMsg(COMMAND_SET_FLY_MODE, atoi(tokens[1]));

    } else if (strcmp(tokens[0], "altitudeholderenabled") == 0) {
        sendMsg(COMMAND_SET_ALTITUDE_HOLD, atoi(tokens[1])); // 0 or 1
    } else if (strcmp(tokens[0], "altitudetarget") == 0) {
        if (tokens[1][0] == '+' || tokens[1][0] == '-')
            sendMsg(COMMAND_INCREMENT_ALTITUDE_TARGET, atoi(tokens[1]));
        else
            sendMsg(COMMAND_SET_ALTITUDE_TARGET, atoi(tokens[1]));

    } else if (strcmp(tokens[0], "tm") == 0) {
        sendMsg(COMMAND_TESTMOTOR_FL, atoi(tokens[2]));
        sendMsg(COMMAND_TESTMOTOR_BL, atoi(tokens[3]));
        sendMsg(COMMAND_TESTMOTOR_FR, atoi(tokens[4]));
        sendMsg(COMMAND_TESTMOTOR_BR, atoi(tokens[5]));

    } else if (strcmp(tokens[0], "takepicture") == 0) {
        //take picture
        char cmd[128];
        memset(cmd, '\0', 128);
        sprintf(cmd, "%s %s &", CAMERA_CMD, tokens[0]);
        ret = system(cmd);
    } else if (strcmp(tokens[0], "vidsnap") == 0) {
        if (strcmp(tokens[2], "record") == 0) {
            char cmd[128];
            memset(cmd, '\0', 128);
            sprintf(cmd, "%s video %s &", CAMERA_CMD, tokens[2]);
            ret = system(cmd);
            recording = 1;
        } else if (strcmp(tokens[2], "stop") == 0) {
            char cmd[128];
            memset(cmd, '\0', 128);
            sprintf(cmd, "%s video %s &", CAMERA_CMD, tokens[2]);
            ret = system(cmd);
            recording = 0;
        } else if (strcmp(tokens[2], "pause") == 0) {
            char cmd[128];
            memset(cmd, '\0', 128);
            sprintf(cmd, "%s video %s &", CAMERA_CMD, tokens[2]);
            ret = system(cmd);
            recording = 2;
        }
    } else if (strcmp(tokens[0], "querystatus") == 0) {
        // yaw pitch roll altitudetarget altitude recording
        snprintf(resp, 255, "status %s %2.2f %2.2f %2.2f %i %i %i %i %i %i %i", tokens[1], avr_s[LOG_QUATERNION_YAW] / 100.0f, avr_s[LOG_QUATERNION_PITCH] / 100.0f, avr_s[LOG_QUATERNION_ROLL] / 100.0f, avr_s[LOG_ALTITUDE_HOLD_TARGET], avr_s[LOG_ALTITUDE], recording, avr_s[LOG_MOTOR_FL], avr_s[LOG_MOTOR_BL], avr_s[LOG_MOTOR_BR], avr_s[LOG_MOTOR_FR]);
        return resp;
    }
    snprintf(resp, 255, "OK %s", tokens[1]);

    return resp;
}

void recvMsgs() {
    static int sel = 0, i = 0, ret = 0;
    static unsigned char buf[4];
    static struct avr_msg m;

    static fd_set fds;
    static struct timeval timeout;

    do {
        FD_ZERO(&fds);
        FD_SET(sock, &fds);
        FD_SET(ssock, &fds);
        timeout.tv_sec = 0;
        timeout.tv_usec = 0; // If the timeout argument points to an object of type struct timeval whose members are 0, select() does not block
        int max_fd = ssock > sock ? ssock : sock;
        sel = select(max_fd + 1, &fds, NULL, NULL, &timeout);
        if ((sel < 0) && (errno != EINTR)) {
            perror("select");
            err = 1;
        } else if (sel && !err && !stop && FD_ISSET(sock, &fds)) {
            ret = read(sock, buf + i, 4 - i);
            if (ret < 0) {
                perror("reading");
                err = 1;
            } else {
                i += ret;
                if (i == 4) {
                    if (buf[0] == 1) {
                        if (verbose) printf("Disconnect request.\n");
                        err = 1;
                        i = 0;
                    } else {
                        m.t = buf[1];
                        m.v = unpacki16(buf + 2);
                        avr_s[m.t] = m.v;
                        i = 0;
                    }
                }
            }
        } else if (sel && !err && !stop && FD_ISSET(ssock, &fds)) {
            sockaddr_in remoteAddr;
            int received_bytes = -1;
            //sockaddr_in from;
            socklen_t fromLength = sizeof (remoteAddr);

            received_bytes = recvfrom(ssock, data, sizeof (data), 0, (sockaddr*) & remoteAddr, &fromLength);
            if (received_bytes == -1) {
                perror("received bytes = -1 \n");
            } else {
                data[received_bytes] = 0;

                if (verbose >= 3) {
                    printf("Received: %s\n", data);
                }

                const char* resp = handle_packet(data, remoteAddr);

                if (strlen(resp) > 0) {
                    if (verbose >= 2) {
                        printf("Send response: %s\n", resp);
                    }

                    if (sendto(ssock, resp, strlen(resp), 0, (sockaddr*) & remoteAddr, (socklen_t) sizeof (remoteAddr)) == -1) {
                        perror(strerror(errno));
                    }
                }
            }
        }
    } while (!err && !stop && sel && ret > 0); //no error happened; select picked up socket state change; read got some data back
}

void catch_signal(int sig) {
    printf("signal: %i\n", sig);
    stop = 1;
}

unsigned long k = 0;

void loop() {
    clock_gettime(CLOCK_REALTIME, &t3);
    lastPacketTime = ts = t1 = t2 = t3;
    if (verbose) printf("Starting main loop...\n");

    while (!err && !stop) {
        // Disable altitude holder if throttle go to max value
        if (alt_hold && ((yprt[3] > config.throttle[MAX] - 50) || (yprt[3] < config.throttle[MIN] - 50))) {
            alt_hold = 0;
            throttle_hold = 0;
            sendMsg(COMMAND_SET_ALTITUDE_HOLD, alt_hold);
        }

        clock_gettime(CLOCK_REALTIME, &t2);
        dt = TimeSpecDiff(&t2, &t1);
        dt_ms = dt->tv_sec * 1000 + dt->tv_nsec / 1000000;
        if (dt_ms < 50) {
            mssleep(50 - dt_ms);
            continue; //do not flood AVR with data - will cause only problems; each loop sends 4 msg; 50ms should be enough for AVR to consume them
        }
        t1 = t2;

        if (throttle_hold) {
            yprt[3] = throttle_target;
        }

        // if no packet for 5sec maybe lost connection -> then try to land
        clock_gettime(CLOCK_REALTIME, &t2);
        dt = TimeSpecDiff(&t2, &lastPacketTime);
        dt_ms = dt->tv_sec * 1000 + dt->tv_nsec / 1000000;
        if (dt_ms > 2500) {
            printf("lost connection\n");
            sendMsg(COMMAND_SET_YAW, 0);
            sendMsg(COMMAND_SET_PITCH, 0);
            sendMsg(COMMAND_SET_ROLL, 0);
            sendMsg(COMMAND_SET_THROTTLE, config.throttle[MIN]);
            lastPacketTime = t2;
        } else {
            sendMsg(COMMAND_SET_YAW, yprt[0]);
            sendMsg(COMMAND_SET_PITCH, yprt[1]);
            sendMsg(COMMAND_SET_ROLL, yprt[2]);
            sendMsg(COMMAND_SET_THROTTLE, yprt[3]);
        }

        recvMsgs();
    }

    sendMsg(COMMAND_SET_THROTTLE, config.throttle[MIN]);
}

void print_usage() {
    printf("-d - run as daemon\n");
    printf("-i [file] - PID file\n");
    printf("-v [level] - verbose mode\n");
    printf("-u [socket] - socket to connect to (defaults to %s)\n", sock_path);
    printf("-l [port] - port to listen on (defaults to 1032)\n");
}

int main(int argc, char **argv) {

    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);

    int option;
    verbose = 0;
    while ((option = getopt(argc, argv, "di:v:u:l:")) != -1) {
        switch (option) {
            case 'd': background = 1;
                break;
            case 'i': strcpy(pidfile, optarg);
                break;
            case 'v': verbose = atoi(optarg);
                break;
            case 'u': strcpy(sock_path, optarg);
                break;
            case 'l': sportno = atoi(optarg);
                break;
            default:
                print_usage();
                return -1;
        }
    }

    if (verbose)
        printf("Opening config: %s\n", CFG_PATH);
    ret = udpconfig_open(&config, CFG_PATH);
    if (ret < 0) {
        printf("Failed to initiate config! [%s]\n", strerror(ret));
        exit(EXIT_FAILURE);
    }
    //flight_threshold = config.throttle[MIN]+50;

    // initialize avr buffer
    for (int i = 0; i < 256; i++)
        avr_s[i] = 0;

    // get and create address of AVRSPI
    bzero((char *) &address, sizeof(address));
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, sock_path);
    addrlen = strlen(address.sun_path) + sizeof(address.sun_family);

    // create address for incoming udp connection
    bzero((char *) &saddress, sizeof (saddress));
    saddress.sin_family = AF_INET;
    saddress.sin_addr.s_addr = INADDR_ANY;
    saddress.sin_port = htons(sportno);

    /* Create socket to listen */
    ssock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ssock < 0) {
        perror("opening server socket");
        exit(EXIT_FAILURE);
    }

    //Binding to desired port number
    if (bind(ssock, (struct sockaddr *) &saddress, sizeof (struct sockaddr_in))) {
        close(ssock);
        perror("binding stream socket");
        exit(EXIT_FAILURE);
    }

    //setting Socket to non blocking mode
    int nonBlocking = 1;
    if (fcntl(ssock, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
        close(ssock);
        perror("failed to set non-blocking socket");
        exit(EXIT_FAILURE);
    }

    // run as daemon
    if (background) {
        if (daemon(0, 0) < 0) {
            close(ssock);
            perror("unable to start as daemon");
            exit(EXIT_FAILURE);
        }
        if (strcmp(pidfile, "") != 0) {
            int fd = open(pidfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            if (ftruncate(fd, 0) == -1)
                printf("Could not truncate PID file '%s'", pidfile);

            char buf[256];
            snprintf(buf, 256, "%ld\n", (long) getpid());
            if ((size_t)write(fd, buf, strlen(buf)) != strlen(buf))
                printf("Writing to PID file '%s'", pidfile);
            close(fd);
        }
    }

    while (!stop) {
        err = 0;
        if (verbose) printf("Opening socket...\n");

        /* Create socket on which to send. */
        sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("opening socket");
            //exit(EXIT_FAILURE);
            err = 1;
        }

        while (!stop && connect(sock, (struct sockaddr *) &address, addrlen) < 0) {
            //close(sock);
            perror("connecting socket");
            sleep(2);
            //exit(EXIT_FAILURE);
            continue;
        }

        if (verbose) printf("Connected to avrspi\n");

        // AVRSPI sync
        uint8_t sock_type = 0;
        write(sock, &sock_type, 1);

        //while (!stop && avr_s[255] < STATUS_ARM_MOTORS) {
        //    sleep(1);
        //}

        // set log mode to gyro+altitude for send info to controller
        sendMsg(COMMAND_SET_LOG_MODE, PARAMETER_LOG_MODE_GYRO_AND_ALTITUDE);
        //sendMsg(COMMAND_SET_LOG_MODE, PARAMETER_LOG_MODE_QUATERNION);

        // discard all received packet until avrspi is not connected (don't flood!)
        int udpBufSize = 0;
        socklen_t optlen = sizeof(udpBufSize);
        setsockopt(ssock, SOL_SOCKET, SO_RCVBUF, &udpBufSize, optlen);

        loop();
        close(sock);

        if (err)
            sleep(2);
    }
    close(ssock);
    if (verbose) printf("Closing.\n");
    exit(EXIT_SUCCESS);
}

