#!/bin/sh
if [ "$1" != "start" ]; then
        echo "stoping"
        killall raspivid
else
        w=$4
        h=$5
        if [ -z $w ]; then
                w=640
        fi
        if [ -z $h ]; then
                h=480
        fi
        raspivid -t 0 -b 500000 -w $w -h $h -fps 20 -g 20 -n -o - | gst-launch-1.0 fdsrc ! h264parse ! rtph264pay config-interval=1 pt=96 ! gdppay ! udpsink port=$3 host=$2 &
        PID=$!
        echo "starting;"
fi

