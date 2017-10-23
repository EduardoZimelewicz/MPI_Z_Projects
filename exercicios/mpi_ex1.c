#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[]){
	MPI_Init(&argc, &argv);
	int myrank;
	char name [100];
	int tarefas = 0;
	int result;
	double init_time, end_time;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Get_processor_name(name, &result);
	init_time = MPI_Wtime();
	/*
	if(myrank == 0){
		tarefas++;
		printf("%d %d %s\n", myrank, result, name);
		printf("sou o MESTRE \n");
	}
	else{
		tarefas++;
		printf("%d %d %s\n", myrank, result, name);
		printf("sou ESCRAVO \n");
	}
	*/
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
	end_time = MPI_Wtime();
	double time = end_time - init_time;
	printf("tempo final: %lf \n", end_time);
	MPI_Finalize();	
}
