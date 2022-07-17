#!/bin/bash


NASM_ARCH_TYPE="elf64"
GCC_ARCH_TYPE="-m64"

MAIN="../src/SoftSvmPoly64.c"
ALGORITHM="../src/algorithm/std64/*.c"
INCLUDED_MODULES="../src/cli/*.c ../src/io/*.c ../src/random/*.c"
OUTPUT="../src/SoftSvmPoly64.out"

PARAMS="../data/arch_3k_100_dp -deg 2 -eta 0.05 -iter 6336 -v"

gcc $GCC_ARCH_TYPE -msse -O0 -no-pie -fopenmp -o $OUTPUT $MAIN $ALGORITHM $INCLUDED_MODULES -lm

if [ $? -ne 0 ]; then
{
    echo "Unable to Compile C $MAIN"
    exit 200
}
fi

if [ $# -ne 0 ]; then
{
     $OUTPUT $@
}
else
{
    $OUTPUT $PARAMS
}
fi