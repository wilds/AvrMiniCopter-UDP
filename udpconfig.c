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

#include "udpconfig.h"
#include <stdio.h>

int udpconfig_open(struct udp_config *config,const char *path) {
    static FILE *f;
    int state = 0;
    char p[128];
    sprintf(p,"%sudp.config%c",path,'\0');
    f = fopen(p,"r");
    if (f == NULL) state = 1; 

    printf("Opening config: %s\n",p);

    if (state ==0) {
		if (fscanf(f,"%i\t%i\n",&config->throttle[0],&config->throttle[1]) != 2) state = 1;
		if (fscanf(f,"%i\t%i\t%i",&config->rec_ypr[0], &config->rec_ypr[1], &config->rec_ypr[2]) != 3) state = 1;
        fclose(f);
        fflush(NULL);
    }

    if (state) {
        printf("No config file or config syntax issue.\n");
	return -1;
        //some default values if no config file
        config->rec_ypr[0] = 135;
        config->rec_ypr[1] = 45;
        config->rec_ypr[2] = 45;
        config->throttle[0] = 1000;
        config->throttle[1] = 2000;
	
        f = fopen(p,"w");
        if (f == NULL) {
                perror("UDPCONTROLLER: Error saving config!\n");
                return 0;
        } else {
		fprintf(f,"%i\t%i\n",config->throttle[0],config->throttle[1]);
		fprintf(f,"%i\t%i\t%i\n",config->rec_ypr[0],config->rec_ypr[1],config->rec_ypr[2]);
	}
	if (f) fclose(f);
    }

    return 0; 
}


