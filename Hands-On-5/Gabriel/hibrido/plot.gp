set title "Hybrid Comparison Time" 

set ylabel "Time(seconds)"
set xlabel "Size"

set style line 1 lt 2 lc rgb "cyan"   lw 2 
set style line 2 lt 2 lc rgb "red"    lw 2
set style line 3 lt 2 lc rgb "yellow" lw 2
set style line 4 lt 2 lc rgb "green"  lw 2
set style line 5 lt 2 lc rgb "blue"   lw 2
set style line 6 lt 2 lc rgb "black"  lw 2
set terminal postscript eps enhanced color

set xtics nomirror
set ytics nomirror
set key top left
set key box

set output 'Hybrid.eps'
set style data lines

plot "comp.data" using 1:2 title "OMP"  ls 6 with linespoints,\
     "comp.data" using 1:3 title "MPI"  ls 4 with linespoints,\
     "comp.data" using 1:4 title "Hybrid"  ls 2 with linespoints