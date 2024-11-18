# inside gnuplot run with: load "name.gp"
reset

fname = "trajectory.dat"

#set xrange[0:10]
set xlabel "t" font ",18"

plot fname using 1:2 title "x(t)" with lines
replot fname using 1:3 title "v(t)" with lines
replot fname using 1:4 title "a(t)" with lines
