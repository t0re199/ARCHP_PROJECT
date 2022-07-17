
#ifndef TYPES_32_INCLUDED

    #define TYPES_32_INCLUDED
    #define ALIGNAMENT_32 0x10
    #define ITEMS_IN_PARALLEL_32 0x4
    #define BLOCK_SIZE_32 0x4

    typedef struct
    {
        float *data,
              *labels,
              *alpha,
              eta;
        
        int items,
            dim,
            degree,
            iter,   
            verboseLevel;
    } config32;

#endif