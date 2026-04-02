#!/bin/bash
set -e
cd "$(dirname "$0")/.."
make SIDE_A_TEST
bin/SIDE_A_TEST input_data/side_a_test.txt
