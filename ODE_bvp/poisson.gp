# inside gnuplot run: load "name.gp"
reset

fname = "poisson.dat"

set xrange[0:20]
set xlabel "r" font ",18"
set ylabel "phi(r)" font ",18"

plot fname index 0 title "s=0." with lines
replot fname index 1 title "s=0.2" with lines
replot fname index 2 title "s=0.4" with lines
replot fname index 3 title "s=0.6" with lines
replot fname index 4 title "s=0.8" with lines
replot fname index 5 title "s=1."  with lines
