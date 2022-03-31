set term png size 1000,600
set output '../parallel.png'

set grid

set ylabel "Time"
#set logscale y

set xlabel "Graph size"

set key left top

plot "../data/parallel.dat" u 1:2 w lp lw 2 ps 1.5 pt 6 title "liste", \
    "../data/parallel.dat" u 1:3 w lp lw 2 ps 1.5 pt 6 title "matrice", \
    "../data/parallel.dat" u 1:4 w lp lw 2 ps 1.5 pt 6 title "liste parallel", \
    "../data/parallel.dat" u 1:5 w lp lw 2 ps 1.5 pt 6 title "matrice parallel"