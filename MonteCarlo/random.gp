reset

fname = "decay.dat"

set xrange[0:500]
set log y
set xlabel "time" font ",18"
set ylabel "N(t)" font ",18"

plot fname using 1:2 index 0 title "MC data" 
replot fname using 1:2 index 1 with lines title "NATOMS * exp(-lambda*x)" 
