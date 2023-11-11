#!/bin/bash

counter=0

function_sleep() {
	echo "Running PID $!"
	sleep 3
}

for i in {1..8}
	do
	function_sleep &
	((counter++))
	echo "Count of processes $counter" > res.txt
	done

jobs
sleep 15
echo "Done!"
jobs
