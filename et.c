#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

extern int PAGE_SIZE;
extern int UPDATE_TIMES;
float etime();

struct arg_struct{
	int n;
	char *p;
};

void *fn(void *argument){
	struct arg_struct *args = (struct arg_struct *)argument;
	int stride = (args->n*1024)/UPDATE_TIMES;
	int i, idx=0;
    if(args->n > 0){
    	for(i=0; i<UPDATE_TIMES; i++){
    		args->p[idx] = 'a';
    		idx += stride;
    	}        
    }
}

float et(int n){
	// Create variable for new thread
	pthread_t child;	
	// Create dynamic memory
	char *p = (char*)calloc(1024*n, sizeof(char));
	if( p == NULL){
		return -100.0;
	}
	// Create variable for function-input parameters
	struct arg_struct input_para;
	input_para.n = n;
	input_para.p = p;
    // Start to record time
	etime();
	if(pthread_create(&child, NULL, fn, (void *)&input_para) !=0){
		free(p);
		return -1.0;
	}
	pthread_join(child, NULL);
	// Return
	float elapse_time = etime();
	free(p);
	return elapse_time;	
}