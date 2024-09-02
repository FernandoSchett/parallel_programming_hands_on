/*
@(#)File:           $sequential-tridiagonal-matrix-handson3.c$
@(#)Last changed:   $Date: 20220407 11:35:00 $
@(#)Purpose:        Add a constant value in a tridiagonal matrix in C
@(#)Author:         muriloboratto 'at' fieb.org.br
@(#)Usage:
@(*) Hotocompile:   gcc sequential-tridiagonal-matrix-handson3.c -o obj
@(*) Hotoexecute:   ./obj
*/

#include <stdio.h>
#include <mpi.h>
#define ORDER 4

void printMatrix (int m[][ORDER]) {
  int i, j;
  for(i = 0; i < ORDER; i++) {
    printf ("| ");
    for (j = 0; j < ORDER; j++) {
      printf ("%3d ", m[i][j]);
    }
    printf ("|\n");
  }
  printf ("\n");
}

int main (int argc, char **argv){

  int k[3] = {100, 200, 300};
  int matrix[ORDER][ORDER], rcv1[ORDER][ORDER], rcv2[ORDER][ORDER], rcv3[ORDER][ORDER], size = ORDER*ORDER;
  int i, j, p, numProc, rank, tag = 10;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Status status;

  switch(rank){
    case 0:
      for(i = 0; i < ORDER; i++) {
        for(j = 0; j < ORDER; j++) {
          if( i == j )
            matrix[i][j] = i + j +1;
          else if(i == (j + 1)) {
            matrix[i][j] = i +  j + 1;
            matrix[j][i] = matrix[i][j];
          } else
           matrix[i][j] = 0;
        }
      }
      printMatrix(matrix);
      for(p = 1; p < numProc; p++){
        MPI_Send(&matrix, size, MPI_INT, p, tag, MPI_COMM_WORLD);
      }
      MPI_Recv(&rcv1, size, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&rcv2, size, MPI_INT, 2, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&rcv3, size, MPI_INT, 3, tag, MPI_COMM_WORLD, &status);
      for(i = 0; i < ORDER; i++){
        matrix[i][i] = rcv1[i][i];
        matrix[i + 1][i] = rcv2[i + 1][i];
        matrix[i][i + 1] = rcv3[i][i + 1];    
      }
      printMatrix(matrix);
      break;

    default:
      MPI_Recv(&matrix, size, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

      for(i = 0; i < ORDER; i++){
        switch(rank){
          case 1:
            matrix[i][i] += k[0];
            break;
          case 2:
            matrix[i + 1][i] += k[1];
            break;
          case 3:
            matrix[i][i + 1] += k[2];
            break;
        }
      }
      MPI_Send(&matrix, size, MPI_INT, 0, tag, MPI_COMM_WORLD);
      break;
  }

  MPI_Finalize();
  return 0;
}
