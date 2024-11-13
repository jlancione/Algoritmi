reset

fname = "gaussian.dat"

set xrange[-2.5:2.5]
set xlabel "x" font ",18"
set ylabel "y" font ",18"

plot fname using 1:2 title "MC data" 
replot 1. / ( sqrt(2 * 3.1415) * .5) * exp(- x*x /.5) with lines title "Gaussian(mu = 0, sigma = 0.5)" 
