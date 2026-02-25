CC=g++
CFLAGS=-std=c++17

# cadmium_v2 is a sibling directory of devs-assignment1/
INCLUDECADMIUM=-I ../cadmium_v2/include

#CREATE BIN, BUILD AND RESULTS FOLDERS DURING BUILD
bin_folder     := $(shell mkdir -p bin)
build_folder   := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

# ===========================================================================
# SIMULATOR
# ===========================================================================
main_parking_system.o: top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) top_model/main.cpp -o build/main_parking_system.o

simulator: main_parking_system.o
	$(CC) -g -o bin/PARKING_SYSTEM_TEST build/main_parking_system.o

# ===========================================================================
# TESTS — Atomic Models
# ===========================================================================
main_ac_a_test.o: test/main_access_control_a_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_access_control_a_test.cpp -o build/main_ac_a_test.o

main_ac_b_test.o: test/main_access_control_b_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_access_control_b_test.cpp -o build/main_ac_b_test.o

main_screen_test.o: test/main_screen_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_screen_test.cpp -o build/main_screen_test.o

ACCESS_CONTROL_A_TEST: main_ac_a_test.o
	$(CC) -g -o bin/ACCESS_CONTROL_A_TEST build/main_ac_a_test.o

ACCESS_CONTROL_B_TEST: main_ac_b_test.o
	$(CC) -g -o bin/ACCESS_CONTROL_B_TEST build/main_ac_b_test.o

SCREEN_TEST: main_screen_test.o
	$(CC) -g -o bin/SCREEN_TEST build/main_screen_test.o

# ===========================================================================
# TESTS — Coupled Models (Level 3)
# ===========================================================================
main_side_a_test.o: test/main_side_a_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_side_a_test.cpp -o build/main_side_a_test.o

main_side_b_test.o: test/main_side_b_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_side_b_test.cpp -o build/main_side_b_test.o

SIDE_A_TEST: main_side_a_test.o
	$(CC) -g -o bin/SIDE_A_TEST build/main_side_a_test.o

SIDE_B_TEST: main_side_b_test.o
	$(CC) -g -o bin/SIDE_B_TEST build/main_side_b_test.o

# ===========================================================================
# TESTS — Coupled Model (Level 2)
# ===========================================================================
main_parking_lot_test.o: test/main_parking_lot_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_parking_lot_test.cpp -o build/main_parking_lot_test.o

PARKING_LOT_TEST: main_parking_lot_test.o
	$(CC) -g -o bin/PARKING_LOT_TEST build/main_parking_lot_test.o

# ===========================================================================
# TESTS — Full System (Integration)
# ===========================================================================
main_full_system_test.o: test/main_full_system_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/main_full_system_test.cpp -o build/main_full_system_test.o

FULL_SYSTEM_TEST: main_full_system_test.o
	$(CC) -g -o bin/FULL_SYSTEM_TEST build/main_full_system_test.o

# ===========================================================================
# GROUPED TARGETS
# ===========================================================================
atomic_tests: ACCESS_CONTROL_A_TEST ACCESS_CONTROL_B_TEST SCREEN_TEST

coupled_tests: SIDE_A_TEST SIDE_B_TEST PARKING_LOT_TEST

integration_test: FULL_SYSTEM_TEST

tests: atomic_tests coupled_tests integration_test

#DEFAULT TARGET — builds everything
all: simulator tests

#CLEAN COMMANDS
clean:
	rm -f bin/* build/*
