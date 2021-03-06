#include <stdio.h>
#include "mpi.h"

int main (int argc, char *argv[]){
	MPI_Init(&argc, &argv);
	int myrank;
	char name [100];
	int result;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Get_processor_name(name, &result);
	if(myrank == 0){
		int x = 2;
		MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		//master();
		printf("master: \n");
		//printf("%d %d %s\n", myrank, result, name);
	}
	else if (myrank == 1){
		//slave();
		printf("slave: ");
		//printf("%d %d %s\n", myrank, result, name);
		int x = 3;
		MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%d \n", x);
	}
	MPI_Finalize();
}
