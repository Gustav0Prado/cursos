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

set ylabel  "MFLOP/s - MatRowVet"
set title   "MFLOP/s - MatRowVet"
set terminal qt 0 title "FLOPS_DP"
plot dir.'plot_op1-FLOPS_DP-SSE.dat' using 1:2 title "<op1-v1>" with linespoints, \
     '' using 1:3 title "<op2-v1>" with linespoints