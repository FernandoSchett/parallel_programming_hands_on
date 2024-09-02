#pr -m -t -s omp.data mpi.data hibrid.data > comp.data

#Montar Speedup (sequencial individual)
#awk '{print $1, "\t",(($2*1000)/($5*1000)), "\t",(($3*1000)/($6*1000)), "\t",(($4*1000)/($7*1000))}' speedComp > speedup.data

#Montar Speedup (sequencial unico do OMP)
awk '{print $1, "\t",(($2*1000)/($5*1000)), "\t",(($2*1000)/($6*1000)), "\t",(($2*1000)/($7*1000))}' speedComp > speedup.data
