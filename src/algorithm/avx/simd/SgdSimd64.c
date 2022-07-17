#include <xmmintrin.h>
#include <stdlib.h>
#include <math.h>

#include "../../../random/Random.h"
#include "SgdSimd64.h"


void sgdSimd64(config64 *config)
{
    double *data = config->data,
          *labels = config->labels,
          *alpha = config->alpha;

    int items = config->items,
        dim = config->dim,
        iter = config->iter,
        deg = config->degree,
        t = 0x0,
        i,
        j;

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


void polyKer64(double* xj, double *xi, int len, int deg, double *acc)
{
    double dot;
    dot64(xj, xi, len, &dot);
    *acc = pow(dot + 1.0, deg);
}
