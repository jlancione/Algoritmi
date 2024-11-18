# inside gnuplot run with: load "name.gp"
reset

fname = "derivative.dat"

set xlabel "x" font ",18"
set ylabel "y" font ",18"
set log x
set log y

plot fname using 1:2 title "FD" 
replot fname using 1:3 title "BD" 
replot fname using 1:4 title "CD" 
replot fname using 1:5 title "Higher order" 
