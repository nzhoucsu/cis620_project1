#include <sys/time.h>
#include <stdio.h>

static struct timeval start_time;
static int flag = 0;

float etime(){
	struct timeval stop_time;
	float sec_time, usec_time;

    gettimeofday(&stop_time, (struct timezone *)NULL);
    if(flag == 1){
    	sec_time = stop_time.tv_sec - start_time.tv_sec;
        usec_time = (stop_time.tv_usec - start_time.tv_usec) / 1000000.0;
        start_time = stop_time;
        return sec_time + usec_time;
    }
    else{
        start_time = stop_time;
        flag = 1;
        return 0.0;
    }
}