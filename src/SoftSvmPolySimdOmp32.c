#include <omp.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <xmmintrin.h>

#include "cli/Cli.h"
#include "cli/SPLog.h"
#include "io/RawIO.h"
#include "random/Random.h"
#include "algorithm/sse/omp/SgdSimdOmp32.h"


int main(int argc, char *argv[])
{
    char *datasetName;
    char outputPath[0x200];

    setSeed(RANDOM_SEED);
    
    config32 *config = malloc(sizeof(config32));

    interact32(config, argv, argc);
    setVerboseLevel(config->verboseLevel);
    
    splog("[*] Running %s\n", argv[0x0]);

    datasetName = basename(strdup(argv[0x1]));
    sprintf(outputPath, "../data/%s_omp32.params", datasetName);

    splog("[*] Staring Algorirthm.\n");
    
    double time = -omp_get_wtime();
    sgdOmp32(config);
    time += omp_get_wtime();
    
    splog("[*] Completed, Elapsed Time %1.3f.\n", time);
    
    splog("[*] Dumping Coefficients.\n");
    dump32(outputPath, config->alpha, config->items, 0x1);
    
    splog("[*] Done.\n");

    _mm_free(config->alpha);
    _mm_free(config->data);
    _mm_free(config->labels);

    free(config);
}
