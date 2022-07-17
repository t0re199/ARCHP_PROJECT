#!/bin/bash

NASM_ARCH_TYPE="elf32"
GCC_ARCH_TYPE="-m32"

MAIN="../src/SoftSvmPoly32.c"
ALGORITHM="../src/algorithm/std32/*.c"
INCLUDED_MODULES="../src/cli/*.c ../src/io/*.c ../src/random/*.c"
OUTPUT="../src/SoftSvmPoly32.out"

PARAMS="../data/arch_3k_100_sp -deg 2 -eta 0.05 -iter 6336 -v"

gcc $GCC_ARCH_TYPE -msse -O0 -no-pie -o $OUTPUT $MAIN $ALGORITHM $INCLUDED_MODULES -lm

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
