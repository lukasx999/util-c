#!/usr/bin/env bash
set -euxo pipefail

cc test.c -Wall -Wextra -std=c99 -pedantic -fsanitize=address -o test
./test
