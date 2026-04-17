#!/bin/bash
set -e
cd "$(dirname "$0")/.."
bin/ACCESS_CONTROL_B_TEST input_data/access_control_b_test.txt
