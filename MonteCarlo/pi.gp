reset

fname = "pi.dat"

#set xrange[-2.5:2.5]
set xlabel "x" font ",18"
set ylabel "y" font ",18"
set log x
set log y

plot fname title "error" 
replot 1/sqrt(x) w lines
