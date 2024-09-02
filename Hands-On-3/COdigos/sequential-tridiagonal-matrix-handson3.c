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
  int matrix[ORDER][ORDER];
  int diagprinc[ORDER], diagsec[ORDER-1], diagsec2[ORDER-1], numberOfProcessors, id, tag = 1000, consta;
  int i, j;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcessors); 
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;


  for(i = 0; i < ORDER; i++) {
    for(j = 0; j < ORDER; j++) {
      if( i == j )
        diagprinc[i] = i + j +1;
      else if(i == (j + 1)) {
        diagsec[j] = i + j + 1;
        diagsec2[j] = diagsec[j];
      } else
      matrix[i][j] = 0;
    }
  }
  switch(id){
    case 0:
      printf("%d %d %d %d    \n", diagprinc[0], diagprinc[1], diagprinc[2], diagprinc[3]);
      printf("%d %d %d    \n", diagsec[0], diagsec[1], diagsec[2]);
      printf("%d %d %d    \n", diagsec2[0], diagsec2[1], diagsec2[2]);

      MPI_Send(&diagprinc, ORDER, MPI_INT, 1, tag, MPI_COMM_WORLD);
      MPI_Send(&diagsec, ORDER-1, MPI_INT, 2, tag, MPI_COMM_WORLD);
      MPI_Send(&diagsec2, ORDER-1, MPI_INT, 3, tag, MPI_COMM_WORLD);

      MPI_Send(&k[0], 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
      MPI_Send(&k[1], 1, MPI_INT, 2, tag, MPI_COMM_WORLD);
      MPI_Send(&k[2], 1, MPI_INT, 3, tag, MPI_COMM_WORLD);
      
      MPI_Recv(&diagprinc, ORDER, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&diagsec, ORDER-1, MPI_INT, 2, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&diagsec2, ORDER-1, MPI_INT, 3, tag, MPI_COMM_WORLD, &status);
    
      printf("%d %d %d %d    \n", diagprinc[0], diagprinc[1], diagprinc[2], diagprinc[3]);
      printf("%d %d %d    \n", diagsec[0], diagsec[1], diagsec[2]);
      printf("%d %d %d    \n", diagsec2[0], diagsec2[1], diagsec2[2]);
      
      for(i = 0; i < ORDER; i++) {
        for(j = 0; j < ORDER; j++) {
          if( i == j )
          matrix[i][j] = diagprinc[i];
          else if(i == (j + 1)) {
            matrix[i][j] = diagsec[j];
            matrix[j][i] = diagsec2[j];
          }
        }
      }

      printMatrix(matrix);
    break;
    
    case 1:
      MPI_Recv(&diagprinc, ORDER, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&consta, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      for(i = 0; i < ORDER; i++)
        diagprinc[i] += consta;
      MPI_Send(&diagprinc, ORDER, MPI_INT, 0, tag, MPI_COMM_WORLD);
    break;

    case 2:
      MPI_Recv(&diagsec, ORDER-1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&consta, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      for(i = 0; i < ORDER-1; i++)
        diagsec[i] += consta;
      MPI_Send(&diagsec, ORDER-1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    break;

    case 3:
      MPI_Recv(&diagsec2, ORDER-1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&consta, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        for(i = 0; i < ORDER-1; i++)
          diagsec2[i] += consta;
        MPI_Send(&diagsec2, ORDER-1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    break;
  //printMatrix(matrix);
  }
  MPI_Finalize();
  return 0;
}
