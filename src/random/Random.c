#include <stdlib.h>

#include "Random.h"


void setSeed(long seed)
{
    srand(seed);
}


int randInt(int max)
{
    return rand() % max;
}


int randIntRange(int min, int max)
{
    return (rand() % (max - min)) + min;
}