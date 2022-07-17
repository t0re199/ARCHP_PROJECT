#include "../../../types/Types32.h"


void sgdBlockWise32(config32 *config);


extern void blockWiseDot32(float *data, float *xi, int len, float *acc);
extern void dot32(float *xj, float *xi, int len, float *acc);
extern void arraysSum32(float* dest, float *src, int len);
extern void selfArrayScalarMult32(float* dest, int len, float scalar);
extern void arrayScalarMult32(float* dest, float *src, int len, float scalar);
void polyKer32(float* xj, float *xi, int len, int deg, float *acc);