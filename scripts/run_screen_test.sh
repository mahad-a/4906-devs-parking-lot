#!/bin/bash
set -e
cd "$(dirname "$0")/.."
bin/SCREEN_TEST input_data/screen_test.txt
