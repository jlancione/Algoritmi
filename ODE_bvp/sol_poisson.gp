# inside gnuplot run with: load "name.gp"
reset

fname = "poisson.dat"

set xrange[0:5]
set xlabel "r" font ",18"
set ylabel "Phi(n)" font ",18"
set grid

plot fname using 1:2 index 1 title "Integration" w lines
replot fname using 1:3 index 1 title "AnaliticalSol" w lines
