#!/bin/bash

# compile the C program
g++ -o f_aloha.exe f_aloha.cpp

# check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# run the program
#./f.exe
