#!/bin/bash
set -e
cd "$(dirname "$0")/.."
make FULL_SYSTEM_TEST
bin/FULL_SYSTEM_TEST input_data/full_system_test.txt
