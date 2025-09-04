reset

set xrange [-2.5:2.5] # Always a good idea to
set yrange [-2.5:2.5] # fix the axis range

set pointsize 3        # symbol size
set style line 2 pt 0  # circle specifications to be used for bob 1

#ntail = 100  # number of points to draw in the tail
ninc = 3    # increment between frames, it's the stepsize in for cycle
npoints = 4000

array A1[npoints]  # x of first bob
array A2[npoints]  # x of second bob
array B1[npoints]  # y of first bob
array B2[npoints]  # y of second bob

set term unknown # to store the points in the arrays, without plotting anything
do for [ii=1:npoints:ninc] {
  plot 'double_pendulum.dat' using (A1[ii]=column(2)):(B1[ii]=column(3)) every ::ii::ii, \
       'double_pendulum.dat' using (A2[ii]=column(4)):(B2[ii]=column(5)) every ::ii::ii
}

set term gif animate delay 2 size 850,850
set output 'dp_trajectory.gif'

# Add the hinge in the center as a black filled circle
set object 1 circle at 0,0 size scr 0.01 \
fillstyle solid fillcolor rgb 'black’

# Add the bobs
set object 2 circle at A1[1],B1[1] front size scr 0.02 \
 fillstyle solid fillcolor rgb '#0000FF’ 

set object 3 circle at A2[1],B2[1] front size scr 0.02 \
 fillstyle solid fillcolor rgb '#FF0000’

# Add the ropes
set arrow 1 nohead lw 2 from 0,0 to A1[1],B1[1] back
set arrow 2 nohead lw 2 from A1[1],B1[1] to A2[1],B2[1] back

# Build frames
 do for [ii=1:npoints:ninc] {
  #im = ((ii - ntail) < 0 ? 1:ii-ntail)  # fix boundary issue with tail points
  title = sprintf ("Step = %d",ii)      # Track time steps in the title
  set title title

  # Update arrow and bobs positions
  set object 2 circle at A1[ii],B1[ii]
  set object 3 circle at A2[ii],B2[ii]

  set arrow 1 from 0,0 to A1[ii],B1[ii]
  set arrow 2 from A1[ii],B1[ii] to A2[ii],B2[ii]

  plot 'double_pendulum.dat' using 4:5 every ::0::ii with lines lt 1 notitle
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
