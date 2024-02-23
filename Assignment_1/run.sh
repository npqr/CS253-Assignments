#!/bin/bash

# ANSI color codes
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Compile the C++ code
g++ main.cpp -o main

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Software Compiled Successfully. Running the software now...${NC}"
    
    # Run the compiled program
    ./main
else
    echo "Compilation failed. Please check the code and try again."
fi
