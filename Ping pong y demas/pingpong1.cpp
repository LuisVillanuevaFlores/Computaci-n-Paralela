#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>

int main(){
	int comm_sz;
	int my_rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	int limit = 20;	

	FILE *archivo;
	char rank[20];
	char ubicacion[20]="../ubica";
	char pinpong[20];
	
	sprintf(rank, "%d.txt", my_rank);
	strcat(ubicacion, rank);
	archivo= fopen(ubicacion, "a+t");
	int pong = 0;
	while(pong<limit){
		if(my_rank %2== 0){
			pong++;
			MPI_Send(&pong, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			sprintf(pinpong, "%d\n", pong);
			fputs(pinpong,archivo);
			MPI_Recv(&pong, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		else{
			MPI_Recv(&pong, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			pong++;
			MPI_Send(&pong, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			sprintf(pinpong, "%d\n", pong);
			fputs(pinpong,archivo);
		}
	}
	
	fclose(archivo);
	MPI_Finalize();
	return 0;
}



