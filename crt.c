#include <stdio.h>
#include <stdlib.h>

#define MAX_DYNAMIC_SPACE 8192
#define KB 1024
const int PAGE_SIZE = 4 * KB;
const int UPDATE_TIMES = (MAX_DYNAMIC_SPACE*KB) / (4*KB);// max_calloc_size/page_size

float ep(int n);
float et(int n);

void main(int argc, char *argv[]){
	float return_val;
    int i;
    if(strcmp(argv[0], "./pcrt") == 0){
        // Run pcrt
        return_val = ep(atoi(argv[1]));
        printf("Running Program: pcrt\n");
        printf("Elapse Time: %.8f\n", return_val);
    }
    else if(strcmp(argv[0], "./tcrt") == 0){
        // Run tcrt
        return_val = et(atoi(argv[1]));
        printf("Running Program: tcrt\n");
        printf("Elapse Time: %.8f\n", return_val);
    }
    else{
        printf("Wrong input! Program terminates.\n");
    }
}    