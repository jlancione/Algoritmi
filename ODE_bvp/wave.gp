# inside gnuplot run with: load "name.gp"
reset

fname = "wave.dat"

#set xrange[0.:1.]
set xlabel "x" font ",18"
set ylabel "phi(x)" font ",18"

plot fname index 0 title "k=1" w lines
replot fname index 1 title "k=2" w lines
replot fname index 2 title "k=3" w lines
replot fname index 3 title "k=4" w lines
replot fname index 4 title "k=5" w lines
