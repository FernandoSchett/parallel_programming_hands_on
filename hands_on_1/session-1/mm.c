/*
File:           mm.c
Last changed:   20220303 11:35:00 
Purpose:        Matrix Multiply Sequential Algorithm in C
Author:         Murilo Boratto  <muriloboratto 'at' fieb.org.br>
Usage:
HowToCompile:   gcc mm.c -o mm -fopenmp
HowToExecute:   ./mm    <size> 
                ./mm      100           
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void initializeMatrix(int *matrix, int size)
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      matrix[i * size + j] = rand() % (10 - 1) * 1;
}

void printMatrix(int *matrix, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
      printf("%d\t", matrix[i * size + j]);
    printf("\n");
  }
  printf("\n");
}

int main (int argc, char **argv)
{

 int size = atoi(argv[1]);  
 int i, j, k;
 double t1, t2;
 int nth;
 nth = atoi(argv[2]);
 omp_set_num_threads(nth);
 
 int  *A = (int *) malloc (sizeof(int)*size*size);
 int  *B = (int *) malloc (sizeof(int)*size*size);
 int  *C = (int *) malloc (sizeof(int)*size*size);

 initializeMatrix(A, size);
 initializeMatrix(B, size);

 t1 = omp_get_wtime();
#pragma omp parallel for private(i,j,k) 
 for(i = 0; i < size; i++)
  for(j = 0; j < size; j++)
    for(k = 0; k < size; k++)
       C[i * size + j] += A[i * size + k] * B[k * size + j];
 t2 = omp_get_wtime();

 printf("%f", t2-t1);
//  printMatrix(A,size);
//  printMatrix(B,size);
//  printMatrix(C,size);

 return 0;

}

