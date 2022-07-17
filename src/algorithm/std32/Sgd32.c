#include <xmmintrin.h>
#include <stdlib.h>
#include <math.h>

#include "../../random/Random.h"
#include "Sgd32.h"



void sgd32(config32 *config)
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
        j;

    float etaInverse = 1.0f / config->eta;

    float *beta = _mm_malloc(items * sizeof(float), ALIGNAMENT_32);
    float *tmpAplha = _mm_malloc(items * sizeof(float), ALIGNAMENT_32);

    for(; t < iter; t++)
    {
        arrayScalarMult32(tmpAplha, beta, items, etaInverse);

        i = randInt(items);

        float *xi = data + (i * dim),
              sum = 0.0f,
              kerAcc;

        for(j = 0x0; j < items; j++)
        {
            polyKer32(data + (j * dim), xi, dim, deg, &kerAcc);
            sum += tmpAplha[j] * kerAcc;
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


void selfArrayScalarMult32(float* dest, int len, float scalar)
{
    int i = 0x0;
    for(; i < len; i++)
    {
        dest[i] *= scalar;
    }
}


void arrayScalarMult32(float* dest, float *src, int len, float scalar)
{
    int i = 0x0;
    for(; i < len; i++)
    {
        dest[i] = src[i] * scalar;
    }
}


void arraysSum32(float* dest, float *src, int len)
{
    int i = 0x0;
    for(; i < len; i++)
    {
        dest[i] += src[i];
    }
}


void polyKer32(float* xj, float *xi, int len, int deg, float *acc)
{
    int k = 0x0;

    float scalarProduct = 1.0f;
    for(; k < len; k++)
    {
        scalarProduct += xj[k] * xi[k];
    }

    *acc = powf(scalarProduct, deg);
}
