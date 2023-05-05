#!/bin/bash

# Define the number of times to run the code
NUM_RUNS=10

# Loop through the number of runs
for ((i=1; i<=$NUM_RUNS; i++))
do
  # Generate a random value for the parameter
  # PARAM_VALUE=$(( $i * 10 ))

  # Print the current run number and parameter value
  echo "Run $i: ";

  # Call your C++ program with the current parameter value
  ./f_aloha.exe  #$PARAM_VALUE

done