#!/bin/bash

# compile the C program
gcc -o f.exe f_aloha.c

# check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# run the program
./f.exe
