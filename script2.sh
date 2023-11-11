#!/bin/bash

count_proc=$(cat res.txt)

if [ ! -f "pids.txt" ] && [ ! -f "rez.txt" ]
	then
	echo "Please run script1.sh"
	exit 1
	fi

for i in {1..3}
	do
	read pid_kill < pids.txt
	if [ -n "$pid_kill" ]
		then
		if kill "$pid_kill"
			then
			sed -i '1d' pids.txt
        		count_proc=$((count_proc - 1))
			echo "Killed process $pid_kill"
		else
			echo "Failed kill process $pid_kill"
		fi
	else
		echo "The process $pid_kill is not active"
	fi
	echo "Processes left: $count_proc"
	echo "Count of processes $count_proc" >  rez.txt
done

