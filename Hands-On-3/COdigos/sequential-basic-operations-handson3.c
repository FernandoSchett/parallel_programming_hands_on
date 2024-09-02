#include <stdio.h>
#include <mpi.h>

#define SIZE 12

int main (int argc, char **argv){

  char operations[] = {'+', '-', '*'};
  char operationsRec;
  int numberOfProcessors, id, to, from, tag = 1000;
  int i, result, value;

  //printf("argc : %d",argc);

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcessors); 
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;

  //int i, sum = 0, subtraction = 0, mult = 1;
  int array[SIZE];
  //printf("id : %d", id);
  switch(id){
    case 0:
      for(i = 0; i < SIZE; i++){
        array[i] = i + 1;
        printf("%d \t",array[i]);
      }
      printf("\n");
      //printf("aaas");
      for(to = 1; to < numberOfProcessors; to++) {
        MPI_Send(&array, SIZE, MPI_INT, to, tag, MPI_COMM_WORLD);
        MPI_Send(&operations[to-1], 1, MPI_CHAR, to, tag, MPI_COMM_WORLD);
        //printf("%c", operations[to-1]);
      }

      for(to = 1; to < numberOfProcessors; to++) {
        MPI_Recv(&value, 1, MPI_INT, to, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&operationsRec, 1, MPI_CHAR, to, tag, MPI_COMM_WORLD, &status);
        printf("Result (%c): %d\n",operationsRec, value);
        //printf("%c", operations[to-1]);
      }
    break;
    
    default:
      
      MPI_Recv(&array, SIZE, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&operationsRec, 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
      
      //printf("%c", operationsRec);
      switch (operationsRec) {
        case '+':
          value = 0;
          for(i = 0; i < SIZE; i++)
            value += array[i];
            //printf("valor %d", value);
          break;
        case '-':
          value = 0;
          for(i = 0; i < SIZE; i++)
            value -= array[i];
          break;
        case '*':
          value = 1;
          for(i = 0; i < SIZE; i++)
            value *= array[i];
          break;
      }
      MPI_Send(&value, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
      MPI_Send(&operationsRec, 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
  }

  //printf("asaa");

  MPI_Finalize();
  return 0;
}