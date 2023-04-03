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

	double* recv_buffer = (double*) malloc(param1 * param2 * sizeof(double));

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	start_time = MPI_Wtime();

	double vector, random_vector;
	double output [param1][param2]; 
	//double** matrix = (double**) malloc(param1 * sizeof(double*));
	

	if (my_rank == 0){
/*
		for (int i = 0; i < param1; i++) {
      		matrix[i] = (double*) malloc(param2 * sizeof(double));
      		for (int j = 0; j < param2; j++) {
        		matrix[i][j] = recv_buffer[i*param2 + j];
      		}
    	}*/
		
		printf("");

		//MPI_Recv(recv_buffer, param1*param2, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	}
	
	else{

		double* send_buffer = (double*) malloc(param1 * param2 * sizeof(double));


	
		// if else conditions for load balancing
		if (my_rank == 1){

			for (int i = 0; i < ((my_rank*(param1*param2))/comm_sz); i++) {
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer[i] += random * random_vector;
    			}
  			}

			MPI_Reduce(send_buffer, recv_buffer, param1*param2, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		}else if(my_rank == 2){

			for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++) {
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer[i] += random * random_vector;
    			}
  			}
			MPI_Reduce(send_buffer, recv_buffer, param1*param2, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		}else if(my_rank == 3){
			for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++) {
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer[i] += random * random_vector;
    			}
  			}
			MPI_Reduce(send_buffer, recv_buffer, (param1*param2), MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		}else if (my_rank == 4){
			for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++) {
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer[i] += random * random_vector;
    			}
  			}
			MPI_Reduce(send_buffer, recv_buffer, (param1*param2), MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		}else if(my_rank == 5){
			for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++) {
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer[i] += random * random_vector;
    			}
  			}
			MPI_Reduce(send_buffer, recv_buffer, (param1*param2), MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		}else if(my_rank==6){
			for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++) {
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer[i] += random * random_vector;
    			}
  			}
			MPI_Reduce(send_buffer, recv_buffer, (param1*param2), MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		}
	}


	end_time = MPI_Wtime();
	MPI_Finalize();
	elapsed_time = end_time - start_time;
	printf("Elapsed time is %f seconds for parallel mxv with %d \n",elapsed_time,my_rank);

	file = fopen(str,"w"); // output
	/*for (int i = 0; i < param1; i++) {
        for (int j = 0; j < param2; j++) {
			fprintf(file, "%0.2f ", matrix[i][j]);
        }
		fprintf(file,"\n");
    }
	free(matrix);*/
	free(recv_buffer);
	return(0);
}