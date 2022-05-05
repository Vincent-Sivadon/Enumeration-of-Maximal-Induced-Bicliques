#!/usr/bin/python3
import statistics
import sys

list = []
with open(sys.argv[1]) as f:
    for line in f:
        list.extend(map(float, line))
        
m = statistics.mean(list)
std = statistics.stdev(list)

print(m, std)
