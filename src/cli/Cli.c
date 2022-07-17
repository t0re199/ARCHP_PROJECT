#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <xmmintrin.h>

#include "Cli.h"
#include "SPLog.h"
#include "../io/RawIO.h"
#include "../err/ErrorCode.h"


void interact32(config32 *config, char *argv[], int argc)
{
    char fname[0x200];
    
    char *dsname,
         *filename;
    
    int i,
        j,
        k,
        tmp;
    
    config->data = NULL;
    config->labels = NULL;
    config->items = 0x0;
    config->dim = 0x0;
    config->degree = -0x1;
    config->eta = -0x1;
    config->iter = -0x1;
    config->alpha = NULL;
    config->verboseLevel = QUITE;

    if (argc < 0x4)
    {
        printf("%s dataset -deg <deg> -eta <eta> -iter <it>\n", argv[0]);
        printf("\nParameters:\n");
        printf("\tdataset: Dataset's name: .data for the data, .labels for the labels;\n");
        printf("\t-deg <deg>: Polynomium's degree;\n");
        printf("\t-eta <eta>: Learning rate\n");
        printf("\t-iter <it>: Number of iterations\n");
        printf("\t-q: Quite\n");
        printf("\t-v: Verbose\n");
        exit(TOO_FEW_PARAMS);
    }

    int par = 0x1;
    while (par < argc)
    {
        if (par == 0x1)
        {
            filename = argv[par];
            par++;
        }
        else if (strcmp(argv[par], "-q") == 0x0)
        {
            config->verboseLevel = QUITE;
            par++;
        }
        else if (strcmp(argv[par], "-v") == 0x0)
        {
            config->verboseLevel = VERBOSE;
            par++;
        }
        else if (strcmp(argv[par], "-deg") == 0x0)
        {
            par++;
            if (par >= argc)
            {
                perror("Missing degree value!\n");
                exit(MISSING_PARAMS);
            }
            config->degree = atoi(argv[par]);
            par++;
        }
        else if (strcmp(argv[par], "-eta") == 0x0)
        {
            par++;
            if (par >= argc)
            {
                perror("Missing eta value!\n");
                exit(MISSING_PARAMS);
            }
            config->eta = atof(argv[par]);
            par++;
        }
        else if (strcmp(argv[par], "-iter") == 0x0)
        {
            par++;
            if (par >= argc)
            {
                perror("Missing iter value!\n");
                exit(MISSING_PARAMS);
            }
            config->iter = atoi(argv[par]);
            par++;
        }
        else
        {
            perror("Illegal config!\n");
            exit(ILLEGAL_PARAMS);
        }
    }

    if (filename == NULL || strlen(filename) == 0x0)
    {
        perror("Missing config file name!\n");
        exit(INVALID_DATASET);
    }

    if (config->degree < 0x1)
    {
        perror("Invalid value of degree parameter!\n");
        exit(INVALID_DEGREE);
    }

    if (config->eta < 0.0f)
    {
        perror("Invalid value of eta parameter!\n");
        exit(INVALID_ETA);
    }

    if (config->iter < 0x0)
    {
        perror("Invalid value of iter parameter!\n");
        exit(INVALID_ITERATION);
    }

    dsname = basename(strdup(filename));
    sprintf(fname, "%s.data", filename);
    config->data = loadAligned32(fname, &config->items, &config->dim, 0.0f);
    sprintf(fname, "%s.labels", filename);
    config->labels = load32(fname, &config->items, &tmp);

    config->alpha = _mm_malloc(config->items * sizeof(float), ALIGNAMENT_32);

    if (config->verboseLevel)
    {
        printf("Input data name: '%s.data'\n", filename);
        printf("Input label name: '%s.labels'\n", filename);
        printf("Dataset size [n]: %d\n", config->items);
        printf("Number of dimensions [d]: %d\n", config->dim);
        printf("Degree: %d\n", config->degree);
        printf("Eta: %f\n", config->eta);
    }
}


void interact64(config64 *config, char *argv[], int argc)
{
    char fname[0x200];
    
    char *dsname,
         *filename;
    
    int i,
        j,
        k,
        tmp;
    
    config->data = NULL;
    config->labels = NULL;
    config->items = 0x0;
    config->dim = 0x0;
    config->degree = -0x1;
    config->eta = -0x1;
    config->iter = -0x1;
    config->alpha = NULL;
    config->verboseLevel = QUITE;

    if (argc < 0x4)
    {
        printf("%s dataset -deg <deg> -eta <eta> -iter <it>\n", argv[0]);
        printf("\nParameters:\n");
        printf("\tdataset: Dataset's name: .data for the data, .labels for the labels;\n");
        printf("\t-deg <deg>: Polynomium's degree;\n");
        printf("\t-eta <eta>: Learning rate\n");
        printf("\t-iter <it>: Number of iterations\n");
        printf("\t-q: Quite\n");
        printf("\t-v: Verbose\n");
        exit(TOO_FEW_PARAMS);
    }

    int par = 0x1;
    while (par < argc)
    {
        if (par == 0x1)
        {
            filename = argv[par];
            par++;
        }
        else if (strcmp(argv[par], "-q") == 0x0)
        {
            config->verboseLevel = QUITE;
            par++;
        }
        else if (strcmp(argv[par], "-v") == 0x0)
        {
            config->verboseLevel = VERBOSE;
            par++;
        }
        else if (strcmp(argv[par], "-deg") == 0x0)
        {
            par++;
            if (par >= argc)
            {
                perror("Missing degree value!\n");
                exit(MISSING_PARAMS);
            }
            config->degree = atoi(argv[par]);
            par++;
        }
        else if (strcmp(argv[par], "-eta") == 0x0)
        {
            par++;
            if (par >= argc)
            {
                perror("Missing eta value!\n");
                exit(MISSING_PARAMS);
            }
            config->eta = atof(argv[par]);
            par++;
        }
        else if (strcmp(argv[par], "-iter") == 0x0)
        {
            par++;
            if (par >= argc)
            {
                perror("Missing iter value!\n");
                exit(MISSING_PARAMS);
            }
            config->iter = atoi(argv[par]);
            par++;
        }
        else
        {
            perror("Illegal config!\n");
            exit(ILLEGAL_PARAMS);
        }
    }

    if (filename == NULL || strlen(filename) == 0x0)
    {
        perror("Missing config file name!\n");
        exit(INVALID_DATASET);
    }

    if (config->degree < 0x1)
    {
        perror("Invalid value of degree parameter!\n");
        exit(INVALID_DEGREE);
    }

    if (config->eta < 0.0f)
    {
        perror("Invalid value of eta parameter!\n");
        exit(INVALID_ETA);
    }

    if (config->iter < 0x0)
    {
        perror("Invalid value of iter parameter!\n");
        exit(INVALID_ITERATION);
    }

    dsname = basename(strdup(filename));
    sprintf(fname, "%s.data", filename);
    config->data = loadAligned64(fname, &config->items, &config->dim, 0.0f);
    sprintf(fname, "%s.labels", filename);
    config->labels = load64(fname, &config->items, &tmp);

    config->alpha = _mm_malloc(config->items * sizeof(double), ALIGNAMENT_64);

    if (config->verboseLevel)
    {
        printf("Input data name: '%s.data'\n", filename);
        printf("Input label name: '%s.labels'\n", filename);
        printf("Dataset size [n]: %d\n", config->items);
        printf("Number of dimensions [d]: %d\n", config->dim);
        printf("Degree: %d\n", config->degree);
        printf("Eta: %f\n", config->eta);
    }
}
