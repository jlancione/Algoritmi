# inside gnuplot run with: load "name.gp"
reset

euler = "conserved_euler.dat"
rk2   = "conserved_rk2.dat"
rk4   = "conserved_rk4.dat"

#set xrange[-2.5:2.5]
set xlabel "Periods" font ",18"
set ylabel "Energy" font ",18"
set log y

plot euler title "Euler"
replot rk2 title "rk2"
replot rk4 title "rk4"

