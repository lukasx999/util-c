#!/usr/bin/env bash
set -euxo pipefail

cc test.c -I./lib -Wall -Wextra -std=c11 -pedantic -fsanitize=address,undefined -ggdb -o test
./test
