#include "../../types/Types64.h"


void sgd64(config64 *config);

void selfArrayScalarMult64(double* dest, int len, double scalar);
void arrayScalarMult64(double* dest, double *src, int len, double scalar);
void arraysSum64(double* dest, double *src, int len);
void polyKer64(double* xj, double *xi, int len, int deg, double *acc);