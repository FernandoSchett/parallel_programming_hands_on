#include <stdio.h>
#include <mpi.h>
#include <math.h>

#define SIZE 12

int main (int argc, char **argv){

  int i,x, resultado, aux, tag = 1000, xrec, coefrec,tent,d, numberOfProcessors, id,to;
  int coef[] = {4,9,10,3};
  int pot[] = {3,2,1};

  x = 2;
  printf("Equação : %d.%d^3 + %d.%d^2 + %d.%d + %d\n",coef[0],x,coef[1],x,coef[2],x,coef[3]);
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcessors); 
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;

  //int i, sum = 0, subtraction = 0, mult = 1;
  //printf("id : %d", id);
  switch(id){
    case 0:
      //printf("aaas");
      for(to = 1; to < numberOfProcessors; to++) {
        MPI_Send(&coef[to-1], 1, MPI_INT, to, tag, MPI_COMM_WORLD);
        MPI_Send(&x, 1, MPI_INT, to, tag, MPI_COMM_WORLD);
        //printf("%c", operations[to-1]);
      }
      MPI_Send(&coef[3], 1, MPI_INT, 3, tag, MPI_COMM_WORLD);

      for(to = 1; to < numberOfProcessors; to++) {
        MPI_Recv(&aux, 1, MPI_INT, to, tag, MPI_COMM_WORLD, &status);
        resultado = resultado + aux;
        printf("Result: %d\n",resultado);
        //printf("%c", operations[to-1]);
      }
    break;
    
    case 1:
      MPI_Recv(&coefrec, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&xrec, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      tent = coefrec * xrec * xrec * xrec;
      MPI_Send(&tent, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    break;
    case 2:
      MPI_Recv(&coefrec, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&xrec, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      tent = coefrec * xrec * xrec;
      MPI_Send(&tent, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    break;

    case 3:
      MPI_Recv(&coefrec, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&xrec, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&d, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      tent = (coefrec * xrec) + d;
      MPI_Send(&tent, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    break;
  //printf("asaa");
  }
  MPI_Finalize();
  return 0;
}