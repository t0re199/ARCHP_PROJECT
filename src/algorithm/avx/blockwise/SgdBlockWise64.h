#include "../../../types/Types64.h"


void sgdBlockWise64(config64 *config);

extern void blockWiseDot64(double *data, double *xi, int len, double *acc);
extern void dot64(double *xj, double *xi, int len, double *acc);
extern void simdReduction64(double *xj, double *xi, double *acc);
extern void arraysSum64(double* dest, double *src, int len);
extern void selfArrayScalarMult64(double* dest, int len, double scalar);
extern void arrayScalarMult64(double* dest, double *src, int len, double scalar);
void polyKer64(double* xj, double *xi, int len, int deg, double *acc);