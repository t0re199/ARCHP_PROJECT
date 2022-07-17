#include <xmmintrin.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "RawIO.h"
#include "../err/ErrorCode.h"
#include "../types/Types32.h"
#include "../types/Types64.h"


void dump32(char *filename, void *data, int rows, int cols)
{
    dump(filename, data, rows, cols, sizeof(float));
}


float* load32(char *filename, int *rows, int *cols)
{
    return load(filename, rows, cols, sizeof(float), ALIGNAMENT_32);
}


float* loadAligned32(char *filename, int *rows, int *cols, float paddingValue)
{
    char bytes[sizeof(float)];
    memcpy(bytes, &paddingValue, sizeof(float));
    return loadAligned(filename, rows, cols, sizeof(float), ALIGNAMENT_32, bytes);
}


void dump64(char *filename, void *data, int rows, int cols)
{
    dump(filename, data, rows, cols, sizeof(double));
}


double* load64(char *filename, int *rows, int *cols)
{
    return load(filename, rows, cols, sizeof(double), ALIGNAMENT_64);
}


double* loadAligned64(char *filename, int *rows, int *cols, double paddingValue)
{
    char bytes[sizeof(double)];
    memcpy(bytes, &paddingValue, sizeof(double));
    return loadAligned(filename, rows, cols, sizeof(double), ALIGNAMENT_64, bytes);
}


void* load(char *filename, int *rows, int *cols, size_t size, int alignament)
{
    FILE* fd;
    
    int bytesRead,
        elements;
    
    fd = fopen(filename, "rb");
    
    if (fd == NULL)
    {
        printf("'%s': bad data file name!\n", filename);
        exit(FILE_NOT_EXISTS);
    }
    
    bytesRead = fread(cols, sizeof(int), 0x1, fd);
    bytesRead = fread(rows, sizeof(int), 0x1, fd);
    
    elements = (*rows) * (*cols);

    void* data = _mm_malloc(size * elements, alignament);
    bytesRead = fread(data, size, elements, fd);
    fclose(fd);
    
    return data;
}


void* loadAligned(char *filename, int *rows, int *cols, size_t size, int alignament, void *paddingValue)
{
    FILE* fd;
    
    void *data;
    
    char *ptr;

    int j = 0x0,
        i = 0x0,
        padding = 0x0,
        rowItems,
        bytesRead,
        spuriusData,
        rowsUnaligned,
        colsUnaligned,
        itemsInParallel;
    
    fd = fopen(filename, "rb");
    
    if (fd == NULL)
    {
        printf("'%s': bad data file name!\n", filename);
        exit(FILE_NOT_EXISTS);
    }

    itemsInParallel = size == sizeof(float) ? ITEMS_IN_PARALLEL_32 : ITEMS_IN_PARALLEL_64;
    
    bytesRead = fread(&colsUnaligned, sizeof(int), 0x1, fd);
    checkReadBytes(bytesRead);
    bytesRead = fread(&rowsUnaligned, sizeof(int), 0x1, fd);
    checkReadBytes(bytesRead);
    
    if(colsUnaligned % itemsInParallel != 0x0)
    {
        padding = itemsInParallel - (colsUnaligned % itemsInParallel);
    }

    rowItems = colsUnaligned + padding;
    
    data = _mm_malloc(size * rowItems * rowsUnaligned, alignament);

    ptr = (char *) data;
    for(; i < rowsUnaligned; i++)
    {
        bytesRead = fread(ptr, size, colsUnaligned, fd);
        checkReadBytes(bytesRead);

        ptr += (colsUnaligned * size);
        
        for(j = 0x0; j < padding; j++)
        {
            memcpy(ptr, paddingValue, size);
            ptr += size;
        }
    }
    fclose(fd);
    
    *rows = rowsUnaligned;
    *cols = rowItems;
    return data;
}


void dump(char *filename, void *data, int rows, int cols, size_t size)
{
    FILE* fd;
    
    int i = 0x0,
        writtenBytes;

    fd = fopen(filename, "wb");
    
    if(data != NULL)
    {
        writtenBytes = fwrite(&cols, 0x4, 0x1, fd);
        checkWrittenBytes(writtenBytes);

        writtenBytes = fwrite(&rows, 0x4, 0x1, fd);
        checkWrittenBytes(writtenBytes);

        for(; i < rows; i++) 
        {
            writtenBytes = fwrite(data, size, cols, fd);
            checkWrittenBytes(writtenBytes);
            data += (size * cols);
        }
    }
    fclose(fd);
}