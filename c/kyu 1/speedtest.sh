#!/bin/bash
N=20
total=0

for i in $(seq 1 $N); do
    t=$( (/usr/bin/time -p ./Skyscraper "2 1 2 3 3 3 3 3 3 1 5 2 2 1 4 4 3 2 3 1 5 3 3 2") 2>&1 | grep real | awk '{print $2}' )
    echo "Run $i: $t s"
    total=$(echo "$total + $t" | bc)
done

average=$(echo "scale=2; $total / $N" | bc)
echo "Average time over $N runs: $average s"
