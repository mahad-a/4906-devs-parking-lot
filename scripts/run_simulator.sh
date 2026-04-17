#!/bin/bash
set -e
cd "$(dirname "$0")/.."
bin/PARKING_SYSTEM_TEST input_data/input.txt
