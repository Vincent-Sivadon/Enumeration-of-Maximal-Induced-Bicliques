#!/usr/bin/python3
import statistics
import sys
list = []
for arg in sys.argv:
    if (arg == sys.argv[0]):
        continue
    list.insert(1,float(arg))
m = 1. *sum(list) / len(list)
print(m, statistics.stdev(list))
