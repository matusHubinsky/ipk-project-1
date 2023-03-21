#!/bin/bash
#   author: Matus Hubinsky
#   xlogin: xhubin04
#   date:   21.03.2023

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
WHITE=$(tput sgr0)

function test() {
    output=$(diff -u $1 $2)
    if [ -z "$output" ]; then
        echo "${GREEN}OK${NC}"
    else
        echo "${RED}WRONG${NC}"
        cat "$1"
        cat "$2"
    fi
}

echo "${WHITE}start."
eval "./ipkcpc -h 127.0.0.1 -p 11111 -m tcp < test/tcp/input.txt > test/tcp/resoult_1.txt"

echo -n "${WHITE}localhost TCP: "
test test/tcp/resoult_1.txt test/tcp/input.txt

echo "${WHITE}end."