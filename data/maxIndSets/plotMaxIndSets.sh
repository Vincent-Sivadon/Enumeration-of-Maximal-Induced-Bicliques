#!/usr/bin/gnuplot
set terminal png notransparent rounded giant font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 24 \
  size 1400,960 
#set logscale x
set xlabel "Graph Size"
set ylabel "Time (s) logarithmic scale"
set logscale y
set title "Temps de recherche des sets indépendants maximaux d'un gaphe aléatoire"

# On the Y axis put a major tick every 5
set xtics 10
set ytics 100
set grid xtics
set grid ytics

set key top center

set xrange [0:122]

set output "maxIndSets.png"
plot "maxIndSets.dat" u 1:2:3 with yerrorlines title "BKpiv" ps 2 pt 7 lw 2 lc 1, \
    "maxIndSets.dat" u 1:4:5 with yerrorlines title "TTT" ps 2 pt 7 lw 2 lc 4, \
    "maxIndSets2.dat" u 1:2:3 with yerrorlines title "Standard" ps 2 pt 7 lw 2 lc 7, \
    "maxIndSets2.dat" u 1:4:5 with yerrorlines title "BK" ps 2 pt 7 lw 2 lc 6