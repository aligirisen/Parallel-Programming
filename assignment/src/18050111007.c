#include <hellomake.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){

    int param1, param2;
	double random;
    char* str;

	

	param1 = atoi(argv[1]);
	param2 = atoi(argv[2]);
	str = argv[3]; 
	double vector[param1];

	FILE *file;
	file = fopen(str,"w");


	double** matrix = (double**) malloc(param1 * sizeof(double*));

	for(int i = 0; i < param1; i++) {
    	matrix[i] = (double*) malloc(param2 * sizeof(double));

		srand(8+i);
		vector[i] = randomGenerator();
		//printf("randomwwww-1 : %f\n",vector[i]);
		
    	for (int j = 0; j < param2; j++){

    		srand(18050111007+j);
			random = randomGenerator();
			matrix[i][j] = random;
			//printf("value:%d = %d , %d\n",matrix[i][j],i,j);
    	}
	}


	double output [param1][param2]; // output
	for (int i = 0; i < param1; i++) {
        for (int j = 0; j < param2; j++) {
            output[i][j] += matrix[i][j] * vector[i];
			 fprintf(file, "%0.2f ", output[i][j]);
        }
		fprintf(file,"\n");
    }


	free(matrix);
	return(0);
}
