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
	double** matrix = (double**) malloc(param1 * sizeof(double*));
	

	if (my_rank == 0){
		for (int i = 0; i < param1; i++) {
      		matrix[i] = (double*) malloc(param2 * sizeof(double));
      		for (int j = 0; j < param2; j++) {
        		matrix[i][j] = recv_buffer[i*param2 + j];
      		}
    	}
		for (int i  = 0; i< param1*param2 ;i++){
			printf("%d.recv element : %ls\n",i,recv_buffer[i]);
		}

		//MPI_Recv(recv_buffer, param1*param2, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
	}
	
	else{

		// if else conditions for load balancing
		if (my_rank == 1){
			double* send_buffer_p1 = (double*) malloc(((param1 * param2)/comm_sz) * sizeof(double));
			MPI_Allreduce(send_buffer_p1, recv_buffer, (param1*param2)/4, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);


			//for (int i = 0; i < ((my_rank*(param1*param2))/comm_sz); i++) 
			for (int i=0; i < ((param1*param2)/comm_sz); i++){
				srand(8+i);
				random_vector = randomGenerator();
				printf("1");
					srand(18050111007+i);
					random = randomGenerator();
					send_buffer_p1[i] += random * random_vector;
    			
  			}

			free(send_buffer_p1);
		}else if(my_rank == 2){
			double* send_buffer_p2 = (double*) malloc(((param1 * param2)/comm_sz) * sizeof(double));
			MPI_Allreduce(send_buffer_p2, recv_buffer, (param1*param2)/4, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

			//for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++) 
			for (int i=0; i < ((param1*param2)/comm_sz); i++){
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer_p2[i] += random * random_vector;
    			}
  			}
			free(send_buffer_p2);
		}else if(my_rank == 3){
			double* send_buffer_p3 = (double*) malloc(((param1 * param2)/comm_sz) * sizeof(double));
			MPI_Allreduce(send_buffer_p3, recv_buffer, (param1*param2)/4, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

			//for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++)
			for (int i=0; i < ((param1*param2)/comm_sz); i++) {
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer_p3[i] += random * random_vector;
    			}
  			}
			free(send_buffer_p3);
		}else if (my_rank == 4){
			double* send_buffer_p4 = (double*) malloc(((param1 * param2)/comm_sz) * sizeof(double));
			MPI_Allreduce(send_buffer_p4, recv_buffer, (param1*param2)/4, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

			//for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++) 
			for (int i=0; i < ((param1*param2)/comm_sz); i++){
				srand(8+i);
				random_vector = randomGenerator();
				printf("4");
    
				srand(18050111007+i);
				random = randomGenerator();
				send_buffer_p4[i] += random * random_vector;
    			
  			}
			free(send_buffer_p4);
		}else if(my_rank == 5){
			double* send_buffer_p5 = (double*) malloc(((param1 * param2)/comm_sz) * sizeof(double));
			MPI_Allreduce(send_buffer_p5, recv_buffer, (param1*param2)/4, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

			//for (int i = (((my_rank-1)*(param1*param2))/comm_sz); i < ((my_rank*(param1*param2))/comm_sz); i++)
			for (int i=0; i < ((param1*param2)/comm_sz); i++) {
				srand(8+i);
				random_vector = randomGenerator();
    			for (int j = 0; j < param2; j++) {
					srand(18050111007+j);
					random = randomGenerator();
					send_buffer_p5[i] += random * random_vector;
    			}
  			}
			free(send_buffer_p5);
		}


	}
	free(recv_buffer);

	end_time = MPI_Wtime();
	MPI_Finalize();
	elapsed_time = end_time - start_time;
	printf("Elapsed time is %f seconds for parallel mxv with %d \n",elapsed_time,my_rank);

	file = fopen(str,"w");  
	for (int i = 0; i < param1; i++) {
        for (int j = 0; j < param2; j++) {
			fprintf(file, "%0.2f ", matrix[i][j]);
        }
		fprintf(file,"\n");
    }
	free(matrix);
	fclose(str);
	
	return(0);
}