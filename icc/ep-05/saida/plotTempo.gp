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

set ylabel  "Segundos"
set title   "Tempo - MatRowVet"
set terminal qt 0 title "Tempo - MatRowVet"
plot 'plot_MatRowVet-Tempo.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints

pause -1

set title   "Tempo - MatMatRow"
set terminal qt 0 title "Tempo - MatMatRow"
plot 'plot_MatMatRow-Tempo.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints