#!/bin/bash

ARGS=(0 nan 42.0f);

for arg in ${ARGS[@]}; do
	COMMAND="./scalar_converter \"$arg\""
	echo ">" $COMMAND;
	eval $COMMAND
	echo
done
