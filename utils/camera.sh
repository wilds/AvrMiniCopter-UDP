#!/bin/sh
PIDFile="raspivid.pid"
PID=$(<"$PIDFile")
case "$1" in
	record)
		if [ -z "$PID" ]
			/usr/bin/raspivid -o /rpicopter/cam/video-$1.h264 -vf -hf -w 1280 -h 720 -fps 25 -b 5000000 -t 30000 &
			PID=$!
			echo $PID > $PIDFile
		else
			kill -s SIGUSR1 $PID
		fi
		;;

	stop)
		kill $PID
		rm $PIDFile
	;;

	pause)
		kill -s SIGUSR1 $PID
	;;
	
	takepicture)
	/usr/bin/raspistill -o /rpicopter/cam/image-$1.jpg  -hf -vf -w 1024 -h 768 -ex sports &
	;;
esac
