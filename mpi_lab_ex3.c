#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#define ARRAYSIZE 16

int main (int argc, char *argv[]){
	MPI_Init(&argc, &argv);
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	int tarefas = 0; 
	MPI_Comm_size(MPI_COMM_WORLD,&tarefas);
	char name[100];
	int result;
	double data[ARRAYSIZE];
	MPI_Get_processor_name(name, &result);
	int parcela = ARRAYSIZE/tarefas;
	double sum = 0;
	double root_sum = 0;
	double *rbuf;
	rbuf = (double *) malloc (tarefas*parcela*sizeof(double));
	
	if(tarefas%2 != 0){
		printf("odd number of tasks \n");
		MPI_Finalize();
	}
	
	if(myrank == 0){
		printf("%d %d %s\n", myrank, result, name);
		printf("sou o MESTRE \n");
		int i;
		
		
		for(i = 0; i < ARRAYSIZE; i++){
			data[i] = i * 1.0;
		}
		
		for(i = 0; i < parcela; i++){
   			data[i] = data[i] + i * 1.0;
   			root_sum += data[i];
		}	
		
		
        int inner_rank = 1;
        int j;
        for (j = parcela; j < ARRAYSIZE; j+=parcela){
        	MPI_Send(&data[j], parcela, MPI_DOUBLE, inner_rank, 1, MPI_COMM_WORLD);
        	inner_rank++;
        }
        
	}
	
	if(myrank != 0){
		printf("%d %d %s\n", myrank, result, name);
		printf("sou ESCRAVO \n");
		
		MPI_Recv(data, parcela, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		int i;
		
		for(i = 0; i < parcela; i++){
   			data[i] = data[i] + data[i] * 1.0;
   			sum += data[i];
		}
		
		/*
		printf(" minha parcela [%d]: ", myrank);
        for (int i=0; i<parcela; i++)
            printf("%lf ", data[i]);
        printf("\n");
        printf("%lf \n", sum);	
		*/
	}
	
	double partial_sum;
	MPI_Gather(data, parcela, MPI_DOUBLE, rbuf, parcela, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Reduce(&sum, &partial_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	
	if(myrank == 0){
	printf("buf do mestre [%d]: ", myrank);
        for (int i=0; i<(tarefas*parcela); i++)
            printf("%lf ", rbuf[i]);
        printf("\n");
        free(rbuf);
        printf("%lf \n", root_sum + partial_sum);
	}
	
	MPI_Finalize();
	return 0;	
}


