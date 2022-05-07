#!/usr/bin/gnuplot
set terminal png notransparent rounded giant font "/usr/share/fonts/truetype/msttcorefonts/arial.ttf" 24 \
  size 1400,960 
#set logscale x
set xlabel "Nombre de threads OpenMP"
set ylabel "Time (s)"
#set logscale y
set title "Scalabilite de la version finale"

# On the Y axis put a major tick every 5
set xtics 4
set ytics 0.3
set grid xtics
set grid ytics

set key top left

set xrange [0:66]

set output "scalabilite.png"
plot "scalabilite.dat" u 1:2:3 with yerrorlines title "1 MPI rank" ps 2 pt 7 lw 2 lc 1, \
    "scalabilite.dat" u 1:4:5 with yerrorlines title "2 MPI ranks"  ps 2 pt 7 lw 2 lc 4, \
    "scalabilite.dat" u 1:6:7 with yerrorlines title "4 MPI ranks"  ps 2 pt 7 lw 2 lc 7, \
    "scalabilite.dat" u 1:8 title "linear scalability with 4 MPI ranks (ideal)" w lp ps 2 pt 7 lw 2 lc 3