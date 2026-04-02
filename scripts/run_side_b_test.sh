#!/bin/bash
set -e
cd "$(dirname "$0")/.."
make SIDE_B_TEST
bin/SIDE_B_TEST input_data/side_b_test.txt
