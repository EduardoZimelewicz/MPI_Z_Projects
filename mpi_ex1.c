#include <stdio.h>
#include "mpi.h"

int main (int argc, char *argv[]){
	MPI_Init(&argc, &argv);
	int myrank;
	char name [100];
	int tarefas = 0;
	int result;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Get_processor_name(name, &result);
	if(myrank == 0){
		//master();
		tarefas++;
		printf("%d %d %s\n", myrank, result, name);
		printf("sou o MESTRE \n");
	}
	else{
		//slave();
		tarefas++;
		printf("%d %d %s\n", myrank, result, name);
		printf("sou ESCRAVO \n");
	}
	
	if(tarefas % 2 != 0){
		MPI_Finalize();	
	}
	
	int fontrank = 0;
	int destino = 0;
	else if(myrank < (tarefas/2)){
		destino = (tarefa/2) + myrank;
		MPI_Send(&myrank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
		MPI_Recv(&fontrank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
	else{
		destino = (tarefa/2) - myrank;
		MPI_Send(&myrank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
		MPI_Recv(&fontrank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
	printf("Tarefa %d enviou tarefa para %d \n", myrank, destino);
	MPI_Finalize();	
}
