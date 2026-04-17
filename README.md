# Parking Lot DEVS Simulation (Cadmium v2)

A discrete-event simulation of a parking lot. Cars arrive at an entrance gate, get tracked by sensors on each side of the lot, and the available-space count on the screen decrements accordingly. When a car leaves, it passes through the exit gate.

## Prerequisites

- g++ with C++17 support
- Cadmium v2

## Building

```
./build_sim.sh
make all              # build simulator + all 7 tests
make simulator        # build only bin/PARKING_SYSTEM_TEST
make atomic_tests     # build ACCESS_CONTROL_A/B_TEST + SCREEN_TEST
make coupled_tests    # build SIDE_A/B_TEST + PARKING_LOT_TEST
make integration_test # build FULL_SYSTEM_TEST
make clean            # remove all binaries and object files
```

Binaries go into `bin/`, object files into `build/`, and CSV logs into `simulation_results/`.

## Directory Structure

```
├── atomics
│   ├── access_control.hpp
│   ├── screen.hpp
│   └── sensor.hpp
├── bin
│   ├── ACCESS_CONTROL_A_TEST
│   ├── ACCESS_CONTROL_B_TEST
│   ├── FULL_SYSTEM_TEST
│   ├── PARKING_LOT_TEST
│   ├── PARKING_SYSTEM_TEST
│   ├── SCREEN_TEST
│   ├── SIDE_A_TEST
│   └── SIDE_B_TEST
├── build
│   ├── main_ac_a_test.o
│   ├── main_ac_b_test.o
│   ├── main_full_system_test.o
│   ├── main_parking_lot_test.o
│   ├── main_parking_system.o
│   ├── main_screen_test.o
│   ├── main_side_a_test.o
│   └── main_side_b_test.o
├── coupled
│   ├── parking_lot.hpp
│   ├── parking_system.hpp
│   └── side.hpp
├── DEVSmodelsForm.doc
├── existing_model
│   ├── AccessControlType.cpp
│   ├── AccessControlType.h
│   ├── form_ParkingLot.doc
│   ├── makefile
│   ├── ModelDescription-ParkingLot.xml
│   ├── notes1.txt
│   ├── ParkingLotbat
│   ├── ParkingLot.docx
│   ├── ParkingLot.ev
│   ├── ParkingLotLOG_9.log
│   ├── ParkingLot.ma
│   ├── ParkingLot.madesigner
│   ├── ParkingLotOUT_9.out
│   ├── read.me
│   ├── register.cpp
│   ├── ScreenType.cpp
│   ├── ScreenType.h
│   ├── Sensor1Type.cpp
│   └── Sensor1Type.h
├── input_data
│   ├── access_control_a_test.txt
│   ├── access_control_b_test.txt
│   ├── full_system_test.txt
│   ├── input.txt
│   ├── parking_lot_test.txt
│   ├── screen_test.txt
│   ├── side_a_test.txt
│   └── side_b_test.txt
├── makefile
├── README.md
├── scripts
│   ├── run_all_tests.sh
│   ├── run_access_control_a_test.sh
│   ├── run_access_control_b_test.sh
│   ├── run_screen_test.sh
│   ├── run_side_a_test.sh
│   ├── run_side_b_test.sh
│   ├── run_parking_lot_test.sh
│   ├── run_full_system_test.sh
│   └── run_simulator.sh
├── simulation_results
│   ├── access_control_a_test.csv
│   ├── access_control_b_test.csv
│   ├── full_system_test.csv
│   ├── parking_lot_test.csv
│   ├── parking_system_test.csv
│   ├── screen_test.csv
│   ├── side_a_test.csv
│   └── side_b_test.csv
├── test
│   ├── main_access_control_a_test.cpp
│   ├── main_access_control_b_test.cpp
│   ├── main_full_system_test.cpp
│   ├── main_parking_lot_test.cpp
│   ├── main_screen_test.cpp
│   ├── main_side_a_test.cpp
│   └── main_side_b_test.cpp
└── top_model
    └── main.cpp
```

Signal flow: AccessControlA → ParkingLot → AccessControlB


## Running the main simulation

```
bin/PARKING_SYSTEM_TEST input_data/input.txt
```

Runs the full system with car arrivals at t=0, t=10, t=20. Each car takes 13 seconds to travel through the entire system (5s entrance + 2s sensors + 1s screen + 5s exit). Output is logged to `simulation_results/parking_system_test.csv`.

---

## Tests

### Atomic model tests

These test individual atomic models in isolation to verify their core behaviour.

| Binary | Input file | What it tests | Input times | Expected outputs |
|---|---|---|---|---|
| `ACCESS_CONTROL_A_TEST` | `access_control_a_test.txt` | Entrance gate | t=1, 11, 21 | t=6, 16, 26 |
| `ACCESS_CONTROL_B_TEST` | `access_control_b_test.txt` | Exit gate | t=3, 13, 23 | t=8, 18, 28 |
| `SCREEN_TEST` | `screen_test.txt` | Space counter | t=2, 7, 12 | t=3 (49), 8 (48), 13 (47) |

### Coupled model tests

These test subsystems where multiple atomics interact together.

| Binary | Input file | What it tests | Input times | Expected outputs |
|---|---|---|---|---|
| `SIDE_A_TEST` | `side_a_test.txt` | Side A  | t=1, 10, 20 | t=3, 12, 22 |
| `SIDE_B_TEST` | `side_b_test.txt` | Side B  | t=2, 12, 22 | t=4, 14, 24 |
| `PARKING_LOT_TEST` | `parking_lot_test.txt` | Parking lot | t=1, 10, 20 | t=4, 13, 23 |

### Integration test

Tests the full hierarchy end-to-end.

| Binary | Input file | What it tests | Input times | Expected outputs |
|---|---|---|---|---|
| `FULL_SYSTEM_TEST` | `full_system_test.txt` | Entrance gate → lot → exit gate | t=1, 20, 40 | t=14, 33, 53 |

To run any test manually:
```
bin/<BINARY_NAME> input_data/<input_file>
```

### Running tests via scripts

Scripts are in `scripts/`. Make them executable once:
```
chmod +x scripts/*.sh
```

Then run individual tests:
```
scripts/run_access_control_a_test.sh
scripts/run_access_control_b_test.sh
scripts/run_screen_test.sh
scripts/run_side_a_test.sh
scripts/run_side_b_test.sh
scripts/run_parking_lot_test.sh
scripts/run_full_system_test.sh
scripts/run_simulator.sh
```

Or run all tests at once:
```
scripts/run_all_tests.sh
```

`run_all_tests.sh` builds each target, runs it, and prints a pass/fail summary at the end. It exits with a non-zero code if any test fails.

---

## Reading the CSV logs

Each row in a log file has the format: `time ; component_path ; port_name ; value`

- if `port_name` is empty, the row is a state snapshot — the value is sigma (time until the next internal event)
- if `port_name` is filled, the row is an output event — the value is the message that was sent on that port

---

## Developers

Assignment was co-developed by:
* Mahad Ahmed - 101220427
* Yusuf Ibrahim - 101231208
