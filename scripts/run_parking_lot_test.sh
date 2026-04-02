#!/bin/bash
set -e
cd "$(dirname "$0")/.."
make PARKING_LOT_TEST
bin/PARKING_LOT_TEST input_data/parking_lot_test.txt
