set title "OMP Time" 

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

set output 'omp_time.eps'
set style data lines

plot "omp.data" using 1:2 title "Threads=2"  ls 6 with linespoints,\
     "omp.data" using 1:3 title "Threads=4"  ls 4 with linespoints,\
     "omp.data" using 1:4 title "Threads=6"  ls 2 with linespoints,\
     "omp.data" using 1:5 title "Threads=8"  ls 3 with linespoints,\
     "omp.data" using 1:6 title "Threads=10" ls 5 with linespoints