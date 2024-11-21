# inside gnuplot run with: load "name.gp"
reset

fname = "poisson.dat"

set xrange[0:5]
set xlabel "s" font ",18"
set ylabel "Residual(s)" font ",18"
set grid

plot fname index 0 title "Residual(s)" w lines 
