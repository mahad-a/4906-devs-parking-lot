#!/bin/bash
set -e
cd "$(dirname "$0")/.."
make simulator
bin/PARKING_SYSTEM_TEST input_data/input.txt
