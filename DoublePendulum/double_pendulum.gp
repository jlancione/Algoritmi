reset

#set term png  # From now on, plots will be done on png terminal
              # and not on screen

set term gif animate delay 4 size 854,480
set output 'dp_trajectory.gif'

set xrange [-2.5:2.5] # Always a good idea to
set yrange [-2.5:2.5] # fix the axis range

set pointsize 2                         # symbol size
set style line 2 lc rgb '#0060ad' pt 7  # circle specifications to be used for bob 1
set style line 3 lc rgb '#0070ad' pt 7  # circle specifications to be used for bob 2

ntail = 50  # number of points to draw in the tail
ninc = 3    # increment between frames, it's the stepsize in for cycle
npoints = 100

# Add the hinge in the center as a black filled circle
set object circle at first 0,0 size scr 0.01 \
  fillstyle solid fillcolor rgb 'black’ 

do for [ii=1:npoints:ninc] {
  im = ((ii - ntail) < 0 ? 1:ii-ntail)  # fix boundary issue with tail points
  title = sprintf ("Step = %d",ii)      # Track time steps in the title
  set title title

  plot 'double_pendulum.dat' using (x0=$2):(y0=$3):(-x0):(-y0) every ::ii::ii with vectors nohead, \
       'double_pendulum.dat' using 4:5:(x0-$4):(y0-$5) every ::ii::ii with vectors nohead, \
       'double_pendulum.dat' using 4:5 every ::im::ii with lines lt 1  # plot tail

  pause 0.02
}


# NOTES
# with lines gli fa unire i .ini
# lt sta per linetype
# every ::3::15 plots lines 3-15

# i .i da far girare sono 2 (su colonne #e di .dat) e mi piacerebbe metterci i segmenti
# sl .dat devo scrivere coord cartesiane
# e potrei alternare bob 1 e 2 così da poterli collegare con le linee (devo per forza mettere dle linee di 0i?)

# .dat
# t x0 y0 x1 y1
