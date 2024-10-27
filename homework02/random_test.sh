#!/bin/bash

int1_h=$(($RANDOM % 1000))
int1_m=$(($RANDOM % 60))
int2_h=$(($RANDOM % 1000))
int2_m=$(($RANDOM % 60))
dep2_m=$(($RANDOM % 60))
dep2_h=$(($RANDOM % 1000))


while [[ $dep2_h -gt $int2_h || ($dep2_h -eq $int2_h && $dep2_m -gt $int2_m) ]]; do
    dep2_h=$(($RANDOM % 1000))
    dep2_m=$(($RANDOM % 60))
done

time_input="$int1_h:$int1_m $int2_h:$int2_m $dep2_h:$dep2_m"
echo "$time_input"

echo "$time_input" | ./a.out