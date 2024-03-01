#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m'

if [ $# -eq 1 ]; then
    echo -e "${GREEN}Running the software now...${NC}"
    ./main
else
    g++ -w main.cpp -o main ./include/jsoncpp/jsoncpp.cpp

    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Software Compiled Successfully. Running the software now...${NC}"
        
        ./main
    else
        echo "Compilation failed. Please check the code and try again."
    fi
fi 