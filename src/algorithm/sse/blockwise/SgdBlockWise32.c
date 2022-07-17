#include <xmmintrin.h>
#include <stdlib.h>
#include <math.h>

#include "../../../random/Random.h"
#include "SgdBlockWise32.h"



void sgdBlockWise32(config32 *config)
{
    float *dataPtr,
          *tmpAlphaPtr,
          *data = config->data,
          *labels = config->labels,
          *alpha = config->alpha;

    int items = config->items,
        dim = config->dim,
        iter = config->iter,
        deg = config->degree,
        offset = dim * BLOCK_SIZE_32,
        t = 0x0,
        i,
        j,
        k;

    float etaInverse = 1.0f / config->eta;

    float *beta = _mm_malloc(items * sizeof(float), ALIGNAMENT_32),
          *tmpAplha = _mm_malloc(items * sizeof(float), ALIGNAMENT_32),
          *kerAccArray = _mm_malloc(BLOCK_SIZE_32 * sizeof(float), ALIGNAMENT_32);
    
    for(; t < iter; t++)
    {
        arrayScalarMult32(tmpAplha, beta, items, etaInverse);

        i = randInt(items);

        float *xi = data + (i * dim),
              sum = 0.0f,
              kerAcc;
        
        dataPtr = data;
        tmpAlphaPtr = tmpAplha;
        for(j = items; j >= BLOCK_SIZE_32; j -= BLOCK_SIZE_32)
        {
            //blockWise Dot + 1 implicit
            blockWiseDot32(dataPtr, xi, dim, kerAccArray);
            
            #pragma unroll
            for(k = 0x0; k < BLOCK_SIZE_32; k++)
            {
                kerAccArray[k] = powf(kerAccArray[k], deg);
            }

            dot32(kerAccArray, tmpAlphaPtr, BLOCK_SIZE_32, &kerAcc);
            sum += kerAcc;

            dataPtr += offset;
            tmpAlphaPtr += BLOCK_SIZE_32;
        }
        for(; j > 0; j--)
        {
            polyKer32(dataPtr, xi, dim, deg, &kerAcc);
            sum += (*tmpAlphaPtr) * kerAcc;
            dataPtr += dim;
            tmpAlphaPtr++;
        }
        
        if((labels[i] * sum) < 1.0f)
        {
            beta[i] += labels[i];
        }

        arraysSum32(alpha, tmpAplha, items);
    }

    selfArrayScalarMult32(alpha, items, 1.0f / iter);

    _mm_free(beta);
    _mm_free(tmpAplha);
    _mm_free(kerAccArray);
}


void polyKer32(float* xj, float *xi, int len, int deg, float *acc)
{
    float dot;
    dot32(xj, xi, len, &dot);
    *acc = powf(dot + 1.0f, deg);
}
