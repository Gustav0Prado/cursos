#!/usr/bin/gnuplot -c
## set encoding iso_8859_15
set encoding utf
set terminal qt persist
set grid
set style data point
set style function line
set style line 1 lc 3 pt 7 ps 0.3
set boxwidth 1
set xtics
set xrange ["0":]
set xlabel  "N (tamanho da matriz)"

set ylabel  "Miss Ratio"
set title   "L2 Cache Miss Ratio - MatRowVet"
set terminal qt 0 title "L2 Cache Miss Ratio - MatRowVet"
plot 'plot_MatRowVet-L2CACHE.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints

pause -1

set title   "L2 Cache Miss Ratio - MatMatRow"
set terminal qt 0 title "L2 Cache Miss Ratio - MatMatRow"
plot 'plot_MatMatRow-L2CACHE.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
