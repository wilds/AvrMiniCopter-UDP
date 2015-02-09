#!/bin/sh
while [ 1 ]; do
sleep 2;
#RET=`pidof udpcontroller | wc -l`
#if [ "$RET" -eq "0" ]; then
if [ -z `pidof udpcontroller` ] ; then
	/usr/local/bin/camera_streamer.sh stop
	/usr/local/bin/udpcontroller -d -i /var/run/udpcontroller.pid
fi

done

