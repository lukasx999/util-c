#!/usr/bin/env bash
set -euxo pipefail

cc dynarray_test.c -Wall -Wextra -std=c99 -pedantic -o test
./test
