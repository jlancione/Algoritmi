reset

#set term png  # From now on, plots will be done on png terminal
              # and not on screen

set term gif animate delay 4 size 850,850
set output 'dp_trajectory.gif'

set xrange [-2.5:2.5] # Always a good idea to
set yrange [-2.5:2.5] # fix the axis range

set pointsize 3        # symbol size
set style line 2 pt 0  # circle specifications to be used for bob 1

ntail = 50  # number of points to draw in the tail
ninc = 3    # increment between frames, it's the stepsize in for cycle
npoints = 100

array A[2]  # x of the bobs
array B[2]  # y of the bobs

# Initialize arrays
plot 'double_pendulum.dat' using (A[1]=$2):(B[1]=$3) every ::1::1 linestyle 2 notitle, \
     'double_pendulum.dat' using (A[2]=$4):(B[2]=$5) every ::1::1 linestyle 2 notitle

# Add the hinge in the center as a black filled circle
set object 1 circle at 0,0 size scr 0.01 \
fillstyle solid fillcolor rgb 'black’

# Add the bobs
set object 2 circle at A[1],B[1] front size scr 0.02 \
 fillstyle solid fillcolor rgb '#0000FF’ 

set object 3 circle at A[2],B[2] front size scr 0.02 \
 fillstyle solid fillcolor rgb '#FF0000’

# Add the ropes
set arrow 1 nohead lw 2 from A[1],B[1] to A[1],B[1] back
set arrow 2 nohead lw 2 from A[2],B[2] to A[2],B[2] back

# Build frames
do for [ii=1:npoints:ninc] {
  im = ((ii - ntail) < 0 ? 1:ii-ntail)  # fix boundary issue with tail points
  title = sprintf ("Step = %d",ii)      # Track time steps in the title
  set title title

  replot 'double_pendulum.dat' using (A[1]=$2):(B[1]=$3) every ::ii::ii linestyle 2 notitle, \
         'double_pendulum.dat' using (A[2]=$4):(B[2]=$5) every ::ii::ii linestyle 2 notitle, \
         'double_pendulum.dat' using 4:5 every ::im::ii with lines lt 1 notitle

  # Update arrow and bobs positions
  set arrow 1 from 0,0 to A[1],B[1]
  set arrow 2 from A[1],B[1] to A[2],B[2]

  set object 2 circle at A[1],B[1]
  set object 3 circle at A[2],B[2]
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
