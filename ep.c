#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern int PAGE_SIZE;
extern int UPDATE_TIMES;
float etime();
float ep(int n){
	// Create variable for child process
	pid_t cpid;	
	int state_val, i, idx=0;
	int stride = (n*1024)/UPDATE_TIMES;	
	// Create dynamic memory
	char *p = (char*)calloc(n*1024, sizeof(char));
	if( p == NULL){
		return -1.0;
	}
	// Start to record time
	etime();
	// Execution
	if((cpid = fork()) == 0){
		// Child process updates dynamic memory
        if(n > 0){
        	for(i=0; i<UPDATE_TIMES; i++){
        		p[idx] = 'a';
        		idx += stride;
        	}
        }
		_exit(0);
	}
	else{
		waitpid(-1, &state_val, 0);
		float elapse_time = etime();
		free(p);
		// Return
		return elapse_time;
	}	
}