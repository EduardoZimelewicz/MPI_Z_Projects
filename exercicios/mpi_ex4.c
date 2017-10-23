#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main (int argc, char *argv[]){
	MPI_Init(&argc, &argv);
	int myrank;
	int data [10];
	int grp_size = 0;
	int *buf;
  	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	if (myrank ==0) {
		MPI_Comm_size(MPI_COMM_WORLD,&grp_size);
		buf=(int *) malloc(grp_size*10*sizeof(int));
	}
	MPI_Gather(data, 10, MPI_INT, buf, 10, MPI_INT,0,MPI_COMM_WORLD);
	for (int i = 0; i < grp_size*10; i++){
		printf("%d ", data[i]);
	}
	MPI_Finalize();	
}
