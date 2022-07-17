#include <stdlib.h>

#include "../err/ErrorCode.h"


#define checkReadBytes(bytes) if(!bytes) { printf("Unable To Read Data!\n"); exit(IO_READ); }
#define checkWrittenBytes(bytes) if(!bytes){ printf("Unable To Write Data!\n"); exit(IO_WRITE); }


void dump32(char *filename, void *data, int rows, int cols);
float* load32(char *filename, int *rows, int *cols);
float* loadAligned32(char *filename, int *rows, int *cols, float paddingValue);


void dump64(char *filename, void *data, int rows, int cols);
double* load64(char *filename, int *rows, int *cols);
double* loadAligned64(char *filename, int *rows, int *cols, double paddingValue);


void dump(char *filename, void *data, int rows, int cols, size_t size); 
void* load(char *filename, int *rows, int *cols, size_t size, int alignament);
void* loadAligned(char *filename, int *rows, int *cols, size_t size, int alignament, void *paddingValue);