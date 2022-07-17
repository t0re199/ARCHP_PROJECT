#include <xmmintrin.h>
#include <stdlib.h>
#include <math.h>

#include "../../../random/Random.h"
#include "SgdBlockWise64.h"
#include <stdio.h>



void sgdBlockWise64(config64 *config)
{
    double *dataPtr,
           *tmpAlphaPtr,
           *data = config->data,
           *labels = config->labels,
           *alpha = config->alpha;

    int items = config->items,
        dim = config->dim,
        iter = config->iter,
        deg = config->degree,
        offset = dim * BLOCK_SIZE_64,
        t = 0x0,
        i,
        j,
        k;

    double etaInverse = 1.0 / config->eta;

    double *beta = _mm_malloc(items * sizeof(double), ALIGNAMENT_64),
           *tmpAplha = _mm_malloc(items * sizeof(double), ALIGNAMENT_64),
           *kerAccArray = _mm_malloc(BLOCK_SIZE_64 * sizeof(double), ALIGNAMENT_64);
    
    for(; t < iter; t++)
    {
        arrayScalarMult64(tmpAplha, beta, items, etaInverse);

        i = randInt(items);

        double *xi = data + (i * dim),
               sum = 0.0,
               kerAcc;
        
        dataPtr = data;
        tmpAlphaPtr = tmpAplha;
        for(j = items; j >= BLOCK_SIZE_64; j -= BLOCK_SIZE_64)
        {
            //blockWise Dot + 1 implicit
            blockWiseDot64(dataPtr, xi, dim, kerAccArray);
            
            #pragma unroll
            for(k = 0x0; k < BLOCK_SIZE_64; k++)
            {
                kerAccArray[k] = pow(kerAccArray[k], deg);
            }

            simdReduction64(kerAccArray, tmpAlphaPtr, &kerAcc);
            sum += kerAcc;

            dataPtr += offset;
            tmpAlphaPtr += BLOCK_SIZE_64;
        }
        for(; j > 0; j--)
        {
            polyKer64(dataPtr, xi, dim, deg, &kerAcc);
            sum += (*tmpAlphaPtr) * kerAcc;
            dataPtr += dim;
            tmpAlphaPtr++;
        }
        
        if((labels[i] * sum) < 1.0)
        {
            beta[i] += labels[i];
        }

        arraysSum64(alpha, tmpAplha, items);
    }

    selfArrayScalarMult64(alpha, items, 1.0 / iter);

    _mm_free(beta);
    _mm_free(tmpAplha);
    _mm_free(kerAccArray);
}


void polyKer64(double* xj, double *xi, int len, int deg, double *acc)
{
    double dot;
    dot64(xj, xi, len, &dot);
    *acc = pow(dot + 1.0, deg);
}
