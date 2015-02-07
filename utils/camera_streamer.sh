#!/bin/sh
if [ "$1" != "start" ]; then
        echo "stoping"
        killall raspivid
else
        w=$4
        h=$5
        if [ -z $w ]; then
                w=320
        fi
        if [ -z $h ]; then
                h=240
        fi
        raspivid -vf -w $w -h $h -fps 10 -b 400000 -t 0 -g 20 -n -ex auto -o - | gst-launch-1.0 -v fdsrc ! h264parse ! rtph264pay config-interval=1 pt=96 ! udpsink port=$3 host=$2 &
        #raspivid -t 0 -b 500000 -w $w -h $h -fps 20 -g 20 -n -o - | gst-launch-1.0 -v fdsrc ! h264parse ! rtph264pay config-interval=1 pt=96 ! udpsink port=$3 host=$2 &
        PID=$!
        echo "starting;"
fi

