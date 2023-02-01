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

set ylabel  "M/Bytes"
set title   "L3 Bandwidth"
set terminal qt 0 title "L3 Bandwidth"
plot 'plot_MatRowVet-FLOPS_DP-u.dat' title "<sem otimização>" with linespoints, \
     'plot_MatRowVet-FLOPS_DP-o.dat' title "<com otimização>" with linespoints

pause -1
