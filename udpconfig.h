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

#ifndef UDPCONFIG_H
#define UDPCONFIG_H

#include "routines.h"

struct udp_config {
    int throttle[2]; //t min, t_max
    int rec_ypr[3]; //y, p, r
};

extern struct udp_config udpconfig;

int udpconfig_open(struct udp_config *c, const char *path);

#endif

