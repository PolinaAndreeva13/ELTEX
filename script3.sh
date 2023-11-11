#!/bin/bash

echo "Process script1.sh killed"
pkill -P "$(pgrep -f script1.sh)"
