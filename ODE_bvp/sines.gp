# inside gnuplot run with: load "name.gp"
reset

fname = "wave.dat"

#set xrange[0.:1.]
set xlabel "x" font ",18"
set ylabel "phi(x)" font ",18"

plot fname index 0 title "k~pi" w lines
replot fname index 1 title "k=2pi" w lines
replot fname index 2 title "k=3pi" w lines
replot fname index 3 title "k=4pi" w lines
replot fname index 4 title "k=5pi" w lines
replot fname index 5 title "k=6pi" w lines
