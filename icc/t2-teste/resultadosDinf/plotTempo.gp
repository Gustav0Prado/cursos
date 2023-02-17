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

set ylabel  "Segundos"
set title   "Tempo - op1"
set terminal qt 0 title "Tempo - op1"
plot dir.'plot_op1-Tempo.dat' using 1:2 title "<op1-v1>" with linespoints, \
     dir.'plot_op2-Tempo.dat' using 1:2 title "<op2-v1>" with linespoints