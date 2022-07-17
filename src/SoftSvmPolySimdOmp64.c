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
#include "algorithm/avx/omp/SgdSimdOmp64.h"


int main(int argc, char *argv[])
{
    char *datasetName;
    char outputPath[0x200];

    setSeed(RANDOM_SEED);
    
    config64 *config = malloc(sizeof(config64));

    interact64(config, argv, argc);
    setVerboseLevel(config->verboseLevel);

    splog("[*] Running %s\n", argv[0x0]);

    datasetName = basename(strdup(argv[0x1]));
    sprintf(outputPath, "../data/%s_omp64.params", datasetName);

    splog("[*] Staring Algorirthm.\n");

    double time = -omp_get_wtime();
    sgdOmp64(config);
    time += omp_get_wtime();
    
    splog("[*] Completed, Elapsed Time %1.3f.\n", time);
    
    splog("[*] Dumping Coefficients.\n");
    dump64(outputPath, config->alpha, config->items, 0x1);
    
    splog("[*] Done.\n");
    
    _mm_free(config->alpha);
    _mm_free(config->data);
    _mm_free(config->labels);

    free(config);
}
