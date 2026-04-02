#!/bin/bash
cd "$(dirname "$0")/.."

PASS=0
FAIL=0

run_test() {
    local target="$1"
    local binary="$2"
    local input="$3"

    echo "----------------------------------------"
    echo "Building: $target"
    if ! make "$target"; then
        echo "FAIL: build failed for $target"
        ((FAIL++))
        return
    fi

    echo "Running:  bin/$binary $input"
    if bin/"$binary" "$input"; then
        echo "PASS: $target"
        ((PASS++))
    else
        echo "FAIL: $target (exit code $?)"
        ((FAIL++))
    fi
}

# Atomic tests
run_test ACCESS_CONTROL_A_TEST ACCESS_CONTROL_A_TEST input_data/access_control_a_test.txt
run_test ACCESS_CONTROL_B_TEST ACCESS_CONTROL_B_TEST input_data/access_control_b_test.txt
run_test SCREEN_TEST           SCREEN_TEST           input_data/screen_test.txt

# Coupled tests (Level 3)
run_test SIDE_A_TEST           SIDE_A_TEST           input_data/side_a_test.txt
run_test SIDE_B_TEST           SIDE_B_TEST           input_data/side_b_test.txt

# Coupled test (Level 2)
run_test PARKING_LOT_TEST      PARKING_LOT_TEST      input_data/parking_lot_test.txt

# Integration test
run_test FULL_SYSTEM_TEST      FULL_SYSTEM_TEST      input_data/full_system_test.txt

echo "========================================"
echo "Results: $PASS passed, $FAIL failed"
echo "========================================"
[ "$FAIL" -eq 0 ]
