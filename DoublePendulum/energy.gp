reset

set term png size 800,600
set output 'energy.png'

set log y

set style line 2 pt 1
set xlabel "t" font ",18"
set ylabel "E(t)" font ",18"

plot 'double_pendulum.dat' using 1:6 linestyle 2 notitle

