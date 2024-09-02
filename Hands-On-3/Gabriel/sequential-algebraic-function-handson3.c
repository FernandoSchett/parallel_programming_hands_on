/*
@(#)File:           $sequential-algebraic-function-handson3.c$
@(#)Last changed:   $Date: 20220407 11:35:00 $
@(#)Purpose:        Algebraic value applied in a function in C
@(#)Author:         muriloboratto 'at' fieb.org.br
@(#)Usage:
@(*) Hotocompile:   gcc sequential-algebraic-function-handson3.c -o obj
@(*) Hotoexecute:   ./obj
*/

#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char **argv){

  double coefficient[4], total, x, p[3], vars[3], result, w1[2], w2[2], w3[3];
  char c;
  int numOfProc, id, tag1 = 10, tag2 = 20, tag3 = 30;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numOfProc);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;

  switch(id){
    case 0:
      printf ("\nf(x) = a*x^3 + b*x^2 + c*x + d\n");

      for(c = 'a'; c < 'e'; c++) {
        printf ("\nEnter the value of the 'constants' %c:\n", c);
        scanf ("%lf", &coefficient[c - 'a']);
      }

      printf("\nf(x) = %lf*x^3 + %lf*x^2 + %lf*x + %lf\n", coefficient[0], coefficient[1], coefficient[2], coefficient[3]);

      printf("\nEnter the value of 'x':\n");
      scanf("%lf", &x);
      
      w1[0] = coefficient[0];
      w2[0] = coefficient[1];
      w3[0] = coefficient[2];
      w3[1] = coefficient[3];
      w1[1] = w2[1] = w3[2] = x;
      
      MPI_Send(&w1, 2, MPI_DOUBLE, 1, tag1, MPI_COMM_WORLD);
      MPI_Send(&w2, 2, MPI_DOUBLE, 2, tag2, MPI_COMM_WORLD);
      MPI_Send(&w3, 3, MPI_DOUBLE, 3, tag3, MPI_COMM_WORLD);
      
      MPI_Recv(&p[0], 1, MPI_DOUBLE, 1, tag1, MPI_COMM_WORLD, &status);
      MPI_Recv(&p[1], 1, MPI_DOUBLE, 2, tag2, MPI_COMM_WORLD, &status);
      MPI_Recv(&p[2], 1, MPI_DOUBLE, 3, tag3, MPI_COMM_WORLD, &status);
      
      printf("\nf(%lf) = %lf\n", x, p[0]+p[1]+p[2]);
      break;

    case 1:
      printf("case 1");
      MPI_Recv(&vars, 2, MPI_DOUBLE, 0, tag1, MPI_COMM_WORLD, &status);
      //result = vars[0] * pow(vars[1], 3);
      result = vars[0] * vars[1] * vars[1] * vars[1];
      MPI_Send(&result, 1, MPI_DOUBLE, 0, tag1, MPI_COMM_WORLD);
      break;
    case 2:
      MPI_Recv(&vars, 2, MPI_DOUBLE, 0, tag2, MPI_COMM_WORLD, &status);
      //result = vars[0] * pow(vars[1], 2);
      result = vars[0] * vars[1] * vars[1];
      MPI_Send(&result, 1, MPI_DOUBLE, 0, tag2, MPI_COMM_WORLD);
      break;
    case 3:
      MPI_Recv(&vars, 3, MPI_DOUBLE, 0, tag3, MPI_COMM_WORLD, &status);
      result = vars[0] * vars[2] + vars[1];
      MPI_Send(&result, 1, MPI_DOUBLE, 0, tag3, MPI_COMM_WORLD);
      break;
  }

  MPI_Finalize();
  return 0;
}
