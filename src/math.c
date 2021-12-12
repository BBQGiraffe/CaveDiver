#include "math.h"
#include <math.h>
#include <stdlib.h>
int Math_Distance(int x1, int y1, int x2, int y2)
{
	int dist = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
	return sqrtl(dist);
}

float randomFloat()
{
      float r = (float)rand()/(float)RAND_MAX;
      return r;
}