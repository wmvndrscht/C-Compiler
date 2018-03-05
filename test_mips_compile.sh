#!/bin/bash

if [[ -z "$1" ]]; then 
    COMPILER=bin/c_compiler
else
    COMPILER=$1
fi

workingin="test/mips_test/testin"
workingout="test/mips_test/output"

mkdir -p $workingout


for DRIVER in $workingin/*_driver.c ; do
    NAME=$(basename $DRIVER _driver.c)
    TESTCODE=$workingin/$NAME.c
    
    >&2 echo "Test case $NAME"
    
    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o $workingout/${NAME}_driver.o 2> $workingout/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Couldn't compile driver program using GCC."
        continue
    fi
    
    # Compile test function with compiler under test to assembly
    cat $TESTCODE | $COMPILER "-S" > $workingout/$NAME.s  2> $workingout/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Compiler returned error message."
        continue
    fi
    
    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static  $workingout/${NAME}_driver.o $workingout/${NAME}.s -o $workingout/${NAME}.elf 2> $workingout/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Linker returned error message."
        continue
    fi
    
    # Run the actual executable
    qemu-mips $workingout/${NAME}.elf
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : Testcase returned $?, but expected 0."
    fi

    echo "pass"
done
