#include "../../../types/Types32.h"


void sgdOmp32(config32 *config);

extern void dot32(float *xj, float *xi, int len, float *acc);
extern void simdReduction32(float *xj, float *xi, float *acc);
extern void arraysSum32(float* dest, float *src, int len);
extern void selfArrayScalarMult32(float* dest, int len, float scalar);
extern void arrayScalarMult32(float* dest, float *src, int len, float scalar);
void polyKer32(float* xj, float *xi, int len, int deg, float *acc);