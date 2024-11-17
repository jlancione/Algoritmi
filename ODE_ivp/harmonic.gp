# inside gnuplot run with: load "name.gp"
reset

fname = "harmonic.dat"

set xrange[0.:70.]
set xlabel "t" font ",18"
set ylabel "Energy" font ",18"

plot fname index 0 title "PosVerlet" 
replot fname index 1 title "RK2" 
