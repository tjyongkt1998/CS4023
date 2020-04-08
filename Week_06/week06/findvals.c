#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"



int main(int argc, char **argv) {

char *num1;
char *num2;

 if (strcmp(argv[1], "-r") == 0) {
  num1 = argv[2];
  num2 = argv[4];
 }else {
  num1 = argv[4];
  num2 = argv[2];
 }

struct tm *local;
time_t start, end;
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
 for (r1 = 0; r1 < rct; r1++){
    for (c1 = 0; c1 < cct; c1++)
      {
	fscanf(stdin, "%f", &rows[r1][c1]);
      }
 }

  for (r1 = 0; r1 < rct; r1++){
    for (c1 = 0; c1 < cct; c1++)
      {
	if (approxEqual(rows[r1][c1], r, t) == 1)
      {
	fprintf(stdout, "r=%d, c=%d: %.6f\n", r1, c1, rows[r1][c1]);
	count++;
      }
     }
  }


  fprintf(stdout, "Found %d approximate matches.\n", count);

  time(&end);
  local = localtime(&end);
  printf("# End time and date: %s", asctime(local));

  exit(0);
}


