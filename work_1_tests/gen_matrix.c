#include <stdio.h>
#include <stdlib.h>
#define INFTY 99

int main (){

	FILE *f = fopen("matrix1.txt", "w");
	int **edge;
	int N=10;
	int i, j = 0;	

	edge= malloc(N * sizeof(int *));
	for (i = 0; i < N; i++)
	{
		edge[i] = malloc(N * sizeof(int));
	}
	
	fprintf(f, "%d\n", N); 
	
	srand(0);
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
		    if(i == j){
		        edge[i][j] = 0;
		    }

		    else{
		        int r = rand() % 10;
		        int val = (r == 5)? INFTY: r;
		        edge[i][j] = val;
		        edge[j][i] = val;  // If there is edge from i to j, then there
		                           // must be edge from j to i
		    }
		    
		  fprintf(f, "%d ", edge[i][j]);
		}
		fprintf(f, "\n");
	}
	return 0;
}
