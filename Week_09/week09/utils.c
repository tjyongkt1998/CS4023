#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int approxEqual(float no1, float no2, float tol){
float minV = no2 - tol;
float maxV = no2 + tol;
return no1 >= minV && no1 <=maxV;
}
