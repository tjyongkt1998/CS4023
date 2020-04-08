#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <sys/time.h>
#include <omp.h>



int main(int argc, char **argv) {

char *num1;
char *num2;
int vis = 0;


for( int i = 0; i < argc; i++){
   if ((strcmp(argv[i], "-v") == 0)){
    vis = 1;  
 } 
   if ((strcmp(argv[i],"-r") == 0)){
    num1 = argv[i + 1];
  
 } 
   if ((strcmp(argv[i], "-t") == 0)){
    num2 = argv[i+1];
 
 }

}
struct timeval tim;
gettimeofday(&tim, NULL);
double t1=tim.tv_sec+(tim.tv_usec/1000000.0);

struct tm *local;
time_t start;
time(&start);

local = localtime(&start);
printf("# Start time and date: %s", asctime(local));

float r = strtof(num1, 0);
float t = strtof(num2, 0);

int rct, cct;
fscanf(stdin, "%d", &rct);
fscanf(stdin, "%d", &cct);


float** rows = (float **) malloc(rct * sizeof(float *));

if (rows == 0) {
  fprintf(stderr, "Couldn’t alocate sufficient space.\n");
  exit(1);
}

int i;
for (i = 0; i < rct; i++) {
  float* row = (float *) malloc(cct * sizeof(float));
  if (row == 0) {
    fprintf(stderr, "Couldn’t alocate sufficient row space.\n");
    exit(1);
  }
rows[i] = row;
}


int count = 0;
int r1, c1;

 for (r1 = 0; r1 < rct; r1++) {
    for (c1 = 0; c1 < cct; c1++) {
	fscanf(stdin, "%f", &rows[r1][c1]);
      }
 }
#pragma omp parallel for collapse(2)
  for (r1 = 0; r1 < rct; r1++)
    {
    for (c1 = 0; c1 < cct; c1++) 
     {
	if (approxEqual(rows[r1][c1], r, t) == 1)
        {
        if( vis == 1)
        {
	fprintf(stdout, "r=%d, c=%d: %.6f\n", r1, c1, rows[r1][c1]);
        fprintf(stdout, "r=%d, cc=%d: %.6f (thread= %d)\n",r1, c1, rows[r1][c1], omp_get_thread_num());
        }
        #pragma omp atomic
   	count++;
       }
     }
  }


fprintf(stdout, "Found %d approximate matches.\n", count);

gettimeofday(&tim, NULL);
double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
printf("Elapsed time: %.6lf(s)\n", t2-t1);

  exit(0);
}
