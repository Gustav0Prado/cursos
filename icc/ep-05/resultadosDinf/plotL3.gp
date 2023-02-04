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
dir = system("dirname ".ARG0)."/"

set ylabel  "M/Bytes"
set title   "L3 Bandwidth - MatRowVet"
set terminal qt 0 title "L3 Bandwidth - MatRowVet"
plot dir.'plot_MatRowVet-L3.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints

pause -1

set title   "L3 Bandwidth - MatMatRow"
set terminal qt 0 title "L3 Bandwidth - MatMatRow"
plot dir.'plot_MatMatRow-L3.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
