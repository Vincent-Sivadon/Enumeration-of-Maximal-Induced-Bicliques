#!/usr/bin/gnuplot
set terminal png notransparent rounded giant font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 24 \
  size 1400,960 
#set logscale x
set xlabel "Graph Size"
set ylabel "Time (s) logarithmic scale"
set logscale y
set title "Temps d'énumération des bicliques pour p=0.001"

# On the Y axis put a major tick every 5
set xtics 200
set ytics 10
set grid xtics
set grid ytics

set key top left

set xrange [400:3002]

set output "algos0,001.png.png"
plot "algos0,001p.dat" u 1:2:3 with yerrorlines title "Algo1" ps 2 pt 7 lw 2 lc 1, \
    "algos0,001p.dat" u 1:4:5 with yerrorlines title "Algo2" ps 2 pt 7 lw 2 lc 4