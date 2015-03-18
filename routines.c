#include "routines.h"

void packi16(unsigned char *buf, unsigned int i)
{
    *buf++ = i>>8; *buf++ = i;
}

unsigned int unpacki16(unsigned char *buf)
{
    return (buf[0]<<8) | buf[1];
}

unsigned int unpacku16(unsigned char *buf)
{
	return ((unsigned int)buf[0]<<8) | buf[1];
}


void mssleep(unsigned int ms) {
  struct timespec tim;
   tim.tv_sec = ms/1000;
   tim.tv_nsec = 1000000L * (ms % 1000);
   //if(nanosleep(&tim , &tim2) < 0 )
   if(nanosleep(&tim , &tim) < 0 )
   {
      printf("Nano sleep system call failed \n");
   }
}

struct timespec *TimeSpecDiff(struct timespec *ts1, struct timespec *ts2)
{
        static struct timespec ts;
        ts.tv_sec = ts1->tv_sec - ts2->tv_sec;
        ts.tv_nsec = ts1->tv_nsec - ts2->tv_nsec;
        if (ts.tv_nsec < 0) {
                ts.tv_sec--;
                ts.tv_nsec += 1000000000;
        }
        return &ts;
}

void local2avr(struct local_msg *lm, struct avr_msg *am) {
        am->t = lm->t;
        am->v = lm->v;
}

void avr2local(struct avr_msg *am, struct local_msg *lm) {
        lm->c = 0;
        lm->t = am->t;
        lm->v = am->v;
}

void pack_lm(unsigned char *buf,struct local_msg *m) {
	buf[0] = m->c;
	buf[1] = m->t;
	packi16(buf+2,m->v);
}

void unpack_lm(unsigned char *buf,struct local_msg *m) {
	m->c = buf[0];
	m->t = buf[1];
	m->v = unpacki16(buf+2);
}

