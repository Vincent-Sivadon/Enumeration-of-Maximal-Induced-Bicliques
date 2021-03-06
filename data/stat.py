#!/usr/bin/python3
import statistics
import sys

list = []
with open(sys.argv[1]) as f:
    for line in f.readlines():
        if "user" not in line:
            list.append(float(line.strip()))
        
m = statistics.mean(list)
std = statistics.stdev(list)

print(m, std)
