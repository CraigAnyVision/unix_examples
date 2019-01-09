#!/bin/bash

set -e

if [[ -z $1 ]]; then
	printf "Argument required: program name\n"
	exit 1
fi

set -u

readonly TMP_LOG="mem_use.log"

while true; do
	ps -C $1 -o pid=,%mem=,vsz= >> $TMP_LOG
	gnuplot plot_mem.plt
	sleep 1
done
