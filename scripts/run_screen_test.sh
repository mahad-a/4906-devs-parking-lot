#!/bin/bash
set -e
cd "$(dirname "$0")/.."
make SCREEN_TEST
bin/SCREEN_TEST input_data/screen_test.txt
