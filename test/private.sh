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

eval "./ipkcpc -h 127.0.0.1 -p 2023 -m udp < test/udp/input.txt > test/udp/resoult_1.txt"
eval "./ipkcpc -h 127.0.0.1 -p 2023 -m tcp < test/tcp/input.txt > test/tcp/resoult_1.txt"

echo -n "${WHITE}localhost UDP: "
test test/udp/resoult_1.txt test/udp/expected_1.txt
echo -n "${WHITE}localhost TCP: "
test test/tcp/resoult_1.txt test/tcp/expected.txt

eval "./ipkcpc -h 147.229.176.19 -p 10002 -m udp < test/udp/input.txt > test/udp/resoult_2.txt"
eval "./ipkcpc -h 147.229.176.19 -p 10002 -m tcp < test/tcp/input.txt > test/tcp/resoult_2.txt"

echo -n "${WHITE}merlin UDP: "
test test/udp/resoult_2.txt test/udp/expected_2.txt
echo -n "${WHITE}merlin TCP: "
test test/tcp/resoult_2.txt test/tcp/expected.txt
