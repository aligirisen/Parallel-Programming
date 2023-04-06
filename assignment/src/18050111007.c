// Ali Riza Girisen

#include <hellomake.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>


int main(int argc, char *argv[]){

    int param1, param2, comm_sz, my_rank;
	double random, start_time, end_time, elapsed_time;
    char* str;
	

	FILE *file;

	param1 = atoi(argv[1]);
	param2 = atoi(argv[2]);
	str = argv[3];

	

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int balance = param1 / (comm_sz-1);
	
	

	double random_vector[param2]; 
	double** matrix = (double**) malloc(param1 * sizeof(double*));
	double output [balance];

	for (int i = 0; i < param1; i++) {
      	matrix[i] = (double*) malloc(param2 * sizeof(double));}

	
	if (my_rank == 0){

		srand(18050111007);
		start_time = MPI_Wtime();
		// buffer for received messaging X invalid buffer pointer ?
		//double* recv_buffer = (double*) malloc(param1 * param2 * sizeof(double));

		// received and converted to 2d array
	

		for (int i = 0; i < param1; i++) {
			
      		for (int j = 0; j < param2; j++) {
				random = randomGenerator();
        		matrix[i][j] = random;
      		}
    	}
		for (int j = 0; j < param2; j++) {
			random_vector[j] = rand() % 100 + 1; 
      	}

		/*
		my_rank = my_rank + 1;
		while(my_rank < comm_sz){
			MPI_Recv(output, param1*param2, MPI_DOUBLE, my_rank, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(random_vector, param2, MPI_DOUBLE, my_rank, 98, MPI_COMM_WORLD);
			MPI_Send(matrix, param1*param2, MPI_DOUBLE, my_rank, 101, MPI_COMM_WORLD);

			for (int i = 0; i < param1; i++ ){
				for (int j = 0; j < param2 ; j++){
					result_matrix[i][j] = recv_buffer[i*param2 + j];
				}
			}


			my_rank = my_rank + 1;*/
		
		for ( int i = 1 ; i < comm_sz ; i ++){
			
			MPI_Send(random_vector, param2, MPI_DOUBLE, i, 98, MPI_COMM_WORLD);
			MPI_Send(matrix, param1*param2, MPI_DOUBLE, i, 101, MPI_COMM_WORLD);
			MPI_Recv(output, balance, MPI_DOUBLE, i, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		}
		end_time = MPI_Wtime();
		elapsed_time = end_time - start_time;
	
	
		printf("Elapsed time is %f seconds for parallel mxv with %d \n",elapsed_time,my_rank);
		file = fopen(str,"w");  
		for (int i = 0; i < param1*param2; i++) {
			fprintf(file, "%0.2f \n", output[i]);
    	}
		fclose(file);
	}		

	
	
	else{

		MPI_Recv(&matrix[0][0], param1 * param2, MPI_DOUBLE, 0, 101, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&random_vector[0], param2, MPI_DOUBLE, 0, 98, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		int rank_range = (my_rank-1) * balance;
		int rank_endrange = my_rank * balance;
		double result = 0.0;
		double sum = 0.0;
		int count = 0;

			//double* send_buffer_p1 = (double*) malloc(param1 * param2* sizeof(double));


			
			for(int i = rank_range ; i <  rank_endrange; i++){
				for(int j = 0; j < param2; j++){
					sum = matrix[i][j] * random_vector[j];
					result = result + sum;
				}
				output[count] = sum;
				count = count + 1;
				result = 0.0;
			}
		MPI_Send(output, balance, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);
	}
	
	free(matrix);
	MPI_Finalize();
	
	return(0);
}