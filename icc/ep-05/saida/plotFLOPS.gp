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

set ylabel  "MFLOP/s - MatRowVet"
set title   "MFLOP/s - MatRowVet"
set terminal qt 0 title "FLOPS_DP"
plot 'plot_MatRowVet-FLOPS_DP-AVX.dat' using 1:2 title "<AVX sem otimização>" with linespoints, \
     '' using 1:3 title "<AVX com otimização>" with linespoints, \
     'plot_MatRowVet-FLOPS_DP-SSE.dat' using 1:2 title "<SSE sem otimização>" with linespoints, \
     '' using 1:3 title "<SSE com otimização>" with linespoints

pause -1

set ylabel  "MFLOP/s - MatMatRow"
set title   "MFLOP/s - MatMatRow"
set terminal qt 0 title "FLOPS_DP"
plot 'plot_MatMatRow-FLOPS_DP-AVX.dat' using 1:2 title "<AVX sem otimização>" with linespoints, \
     '' using 1:3 title "<AVX com otimização>" with linespoints, \
     'plot_MatMatRow-FLOPS_DP-SSE.dat' using 1:2 title "<SSE sem otimização>" with linespoints, \
     '' using 1:3 title "<SSE com otimização>" with linespoints
