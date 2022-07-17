
#ifndef TYPES_64_INCLUDED

    #define TYPES_64_INCLUDED
    #define ALIGNAMENT_64 0x20
    #define ITEMS_IN_PARALLEL_64 0x4
    #define BLOCK_SIZE_64 0x8

    typedef struct
    {
        double *data,
               *labels,
               *alpha,
               eta;
        
        int items,
            dim,
            degree,
            iter,         
            verboseLevel;
    } config64;

#endif