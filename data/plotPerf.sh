#!/usr/bin/gnuplot
set terminal png notransparent rounded giant font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 24 \
  size 1200,960 
#set logscale x
set xlabel "Graph Size"
set ylabel "Time (s)"
#set logscale x 2
set title "BK Mat OB1 nbThreads=128 nbMPIrank=4"

# On the Y axis put a major tick every 5
set xtics 20
set ytics 8.0
set grid xtics
set grid ytics

set key top left

set xrange [0:202]

set output "bk_mat_128_4.png"
plot "bk_mat_128_4.dat" with yerrorlines title "mat" ps 2 pt 7 lw 2 lc 22, \
"bk_list_128_4.dat" with yerrorlines title "list" ps 2 pt 7 lw 2 lc 23