#!/bin/sh
while [ 1 ]; do
sleep 2;
#RET=`pidof udpcontroller | wc -l`
#if [ "$RET" -eq "0" ]; then
if [ -z `pidof udpcontroller` ] ; then 
	/usr/local/bin/udpcontroller
fi

done

