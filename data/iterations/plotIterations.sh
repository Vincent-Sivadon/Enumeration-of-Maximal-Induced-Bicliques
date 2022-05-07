#!/usr/bin/gnuplot
set terminal png notransparent rounded giant font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 24 \
  size 1400,960 
#set logscale x
set xlabel "Iteration"
set ylabel "Time (s)"
#set logscale y
set title "Variation des temps de chaque iteration"

# On the Y axis put a major tick every 5
set xtics 50
set ytics 0.001
set grid xtics
set grid ytics

set key top right

set xrange [0:322]

set output "itationsPapers.png"
plot "iterationsPapers.dat" title "iterations" ps 2 pt 7 lc 1, \
  0.0008515178167701863 title "average" lw 3 lc 4, \
  0.0025307320763088108 title "average + standard deviation" lw 3 lc 7