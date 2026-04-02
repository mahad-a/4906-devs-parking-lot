#!/bin/bash
set -e
cd "$(dirname "$0")/.."
make ACCESS_CONTROL_A_TEST
bin/ACCESS_CONTROL_A_TEST input_data/access_control_a_test.txt
