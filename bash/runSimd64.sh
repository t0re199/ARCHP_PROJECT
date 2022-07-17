#!/bin/bash


NASM_ARCH_TYPE="elf64"
GCC_ARCH_TYPE="-m64"

NASM_SRC="../src/algorithm/avx/nasm/"

MAIN="../src/SoftSvmPolySimd64.c"
ALGORITHM="../src/algorithm/avx/simd/SgdSimd64.c"
INCLUDED_MODULES="../src/cli/*.c ../src/io/*.c ../src/random/*.c"
NASM_OBJECTS="$NASM_SRC*.o"
OUTPUT="../src/SoftSvmPolySimd64.out"

PARAMS="../data/arch_3k_100_dp -deg 2 -eta 0.05 -iter 6336 -v"

rm $NASM_OBJECTS &> /dev/null

for file in $(ls $NASM_SRC); do
{
    nasm -f $NASM_ARCH_TYPE "$NASM_SRC$file"
    if [ $? -ne 0 ]; then
    {
        echo "Unable to Compile Nasm $file"
        exit 199
    }
    fi
}
done;

gcc $GCC_ARCH_TYPE -msse -O0 -no-pie -o $OUTPUT $MAIN $ALGORITHM $INCLUDED_MODULES $NASM_OBJECTS -lm

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