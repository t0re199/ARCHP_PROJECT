#include "../../types/Types32.h"


void sgd32(config32 *config);

void selfArrayScalarMult32(float* dest, int len, float scalar);
void arrayScalarMult32(float* dest, float *src, int len, float scalar);
void arraysSum32(float* dest, float *src, int len);
void polyKer32(float* xj, float *xi, int len, int deg, float *acc);