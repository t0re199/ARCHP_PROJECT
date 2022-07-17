#include <xmmintrin.h>
#include <stdlib.h>
#include <math.h>

#include "../../random/Random.h"
#include "Sgd64.h"



void sgd64(config64 *config)
{
    double *data = config->data,
           *labels = config->labels,
           *alpha = config->alpha;

    int items = config->items,
        dim = config->dim,
        iter = config->iter,
        deg = config->degree,
        i = 0x0,
        t = 0x0,
        j = 0x0;

    double etaInverse = 1.0 / config->eta;

    double *beta = _mm_malloc(items * sizeof(double), ALIGNAMENT_64);
    double *tmpAplha = _mm_malloc(items * sizeof(double), ALIGNAMENT_64);

    for(; t < iter; t++)
    {
        arrayScalarMult64(tmpAplha, beta, items, etaInverse);

        i = randInt(items);

        double *xi = data + (i * dim),
               sum = 0.0,
               kerAcc;

        for(j = 0x0; j < items; j++)
        {
            polyKer64(data + (j * dim), xi, dim, deg, &kerAcc);
            sum += tmpAplha[j] * kerAcc;
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
}


void selfArrayScalarMult64(double* dest, int len, double scalar)
{
    int i = 0x0;
    for(; i < len; i++)
    {
        dest[i] *= scalar;
    }
}


void arrayScalarMult64(double* dest, double *src, int len, double scalar)
{
    int i = 0x0;
    for(; i < len; i++)
    {
        dest[i] = src[i] * scalar;
    }
}


void arraysSum64(double* dest, double *src, int len)
{
    int i = 0x0;
    for(; i < len; i++)
    {
        dest[i] += src[i];
    }
}


void polyKer64(double* xj, double *xi, int len, int deg, double *acc)
{
    int k = 0x0;

    double scalarProduct = 1.0;
    for(; k < len; k++)
    {
        scalarProduct += xj[k] * xi[k];
    }

    *acc = pow(scalarProduct, deg);
}
