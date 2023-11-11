#!/bin/bash

truncate -s 0 pids.txt
counter=0

echo "Start..."

for i in {1..8}
	do
	sleep 1000 &
	((counter++))
	echo $! >> pids.txt
	echo "Processes counter: $counter"
	echo "$counter" > res.txt
	done

sleep 3600
echo "...End"
