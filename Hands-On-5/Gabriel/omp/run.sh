for i in 100 200 300 400 500 600 700 800 900 1000
do
    if [ $1 -eq 0 ]
    then
        #OMP
        OMP_NUM_THREADS=$2 ./omp $i
    fi
    if [ $1 -eq 1 ]
    then
        #MPI
        mpirun -np $1 ./mpi $i
    fi
    if [ $1 -eq 2 ]
    then
        #HYBRID
        mpirun -np $1 ./hybrid $i $2
    fi
done