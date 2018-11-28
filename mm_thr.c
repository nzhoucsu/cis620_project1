#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

// Definition
const int MATRIX_SIZE  = 160;
const int REPEAT_TIMES = 100;
struct pos_struct{
	int start_p;
	int end_p;
};
struct arg_struct{
	int *matrix_1;	
	int *matrix_2;
	int *matrix_3;
	struct pos_struct p;
};
float etime();
void *fn(void *argument){
	struct arg_struct *args = (struct arg_struct *)argument;
    int *m_1 = args->matrix_1;
    int *m_2 = args->matrix_2;
    int *m_3 = args->matrix_3;
    int s_p  = args->p.start_p;    
    int e_p  = args->p.end_p;
    int a, b, c, sum;
    int i, j, k;
    for(i=s_p; i<e_p; i++){
    	for(j=0; j<MATRIX_SIZE; j++){
    		sum = 0;
    		for(k=0; k<MATRIX_SIZE; k++){
    			a = *(m_1+j*MATRIX_SIZE+k);
    			b = *(m_2+k*MATRIX_SIZE+i);
    			c = a * b;
    			sum += c;
    		}
    		*(m_3+j*MATRIX_SIZE+i) = sum;
    	}
    }
}

// main() program
void main(int argc, char *argv[]){	
	// Check input
	if(MATRIX_SIZE % atoi(argv[1]) != 0){
		printf("Wrong thread number! Program terminates!\n");
		return;
	}
	// Set and initialize variables
	float sum = 0.0;
	time_t t;
	int matrix_1[MATRIX_SIZE][MATRIX_SIZE];	
	int matrix_2[MATRIX_SIZE][MATRIX_SIZE];
	int matrix_3[MATRIX_SIZE][MATRIX_SIZE];
	int i, j, k;
	int thread_num = atoi(argv[1]);
	int thread_vol = MATRIX_SIZE / atoi(argv[1]);	
	struct pos_struct p;	
	struct arg_struct input_para[thread_num];
	pthread_t child[thread_num];
	srand((unsigned) time(&t));
	for(i=0; i<MATRIX_SIZE; i++){		
		for(j=0; j<MATRIX_SIZE; j++){
            matrix_1[i][j] = rand()%10;
            matrix_2[i][j] = rand()%10;
		}
	}
	for(i=0; i<thread_num; i++){
		input_para[i].matrix_1 = &matrix_1[0][0];			
		input_para[i].matrix_2 = &matrix_2[0][0];			
		input_para[i].matrix_3 = &matrix_3[0][0];
		input_para[i].p.start_p = i * thread_vol;
		input_para[i].p.end_p   = (i+1) * thread_vol;
	}				
	// Run
	for(i=0; i<REPEAT_TIMES; i++){
		for(k=0; k<MATRIX_SIZE; k++){
			for(j=0; j<MATRIX_SIZE; j++){
	            matrix_3[k][j] = 0;
			}
		}
		// Start to record time
		etime();
		for(j=0; j<thread_num; j++){
			if(pthread_create(&child[j], NULL, fn, (void *)&input_para[j]) !=0){
				printf("Create new thread failed! Program terminates!\n");
				return;
			}
		}
		for (j=0; j<thread_num; j++){
			pthread_join(child[j], NULL);
		}
		sum += etime();
	}
	printf("thread_num = %d, computation_time = %.5f\n", thread_num, sum / REPEAT_TIMES);			
}