# inside gnuplot run with: load "name.gp"
reset

fname = "convergence.dat"

set xrange [0.001:2]
set xlabel "dt" font ",18"
set ylabel "Abs err" font ",18"
set log x
set log y

set title "Convergence study" 

plot fname using   1:3 title "Euler"
replot fname using 1:4 title "RK2"
replot fname using 1:5 title "RK4"
