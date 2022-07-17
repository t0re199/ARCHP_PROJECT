#include <xmmintrin.h>
#include <stdlib.h>
#include <math.h>

#include "../../../random/Random.h"
#include "SgdSimdOmp32.h"


#define THREAD_BLOCK 0x4


void sgdOmp32(config32 *config)
{
    float *data = config->data,
          *labels = config->labels,
          *alpha = config->alpha;

    int items = config->items,
        dim = config->dim,
        iter = config->iter,
        deg = config->degree,
        t = 0x0,
        i,
        k,
        j;

    float etaInverse = 1.0f / config->eta;

    float *beta = _mm_malloc(items * sizeof(float), ALIGNAMENT_32);
    float *tmpAplha = _mm_malloc(items * sizeof(float), ALIGNAMENT_32);

    for(; t < iter; t++)
    {
        arrayScalarMult32(tmpAplha, beta, items, etaInverse);

        i = randInt(items);

        float *xi = data + (i * dim),
              sum = 0.0f;

        for(j = 0x0; j < items / THREAD_BLOCK; j++)
        {
            #pragma omp parallel shared(sum)
            {
                float kerAcc;
                #pragma omp for
                for(k = 0x0; k < THREAD_BLOCK; k++)
                {
                    polyKer32(data + (j * THREAD_BLOCK * dim) + k * dim, xi, dim, deg, &kerAcc);
                    kerAcc *= tmpAplha[j * THREAD_BLOCK + k];
                }

                #pragma omp critical
                {
                    sum += kerAcc;
                }
            }
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
}


void polyKer32(float* xj, float *xi, int len, int deg, float *acc)
{
    float dot;
    dot32(xj, xi, len, &dot);
    *acc = powf(dot + 1.0f, deg);
}
