#!/bin/bash

counter=0

function_sleep() {
	echo "Running PID $!"
	sleep 2
	echo "Stop PID $!"
}

for i in {1..5}
	do
	function_sleep &
	((counter++))
	done
wait
echo "Count of processes $counter" > res.txt
sleep 3600
