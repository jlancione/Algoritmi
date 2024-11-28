# inside gnuplot run with: load "name.gp"
reset

fname = "qho.dat"

set yrange[-0.5:10]
set xlabel "x" font ",18"
set ylabel "phi(x)" font ",18"

plot fname index 0 title "Forward" 
replot fname index 1 title "Backward" 
