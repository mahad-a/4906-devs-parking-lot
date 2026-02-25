CC=g++
CFLAGS=-std=c++17

# Adjust these paths to point at your cadmium and DESTimes installations.
# From devs-assignment1/ the sibling layout expected by the examples would be:
#   ../cadmium/include   →  <repo-root>/cadmium/include
#   ../DESTimes/include  →  <repo-root>/DESTimes/include
INCLUDECADMIUM=-I ../cadmium/include
INCLUDEDESTIMES=-I ../DESTimes/include

#CREATE BIN, BUILD AND RESULTS FOLDERS DURING BUILD
bin_folder     := $(shell mkdir -p bin)
build_folder   := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE THE SIMULATOR
main_parking_lot.o: top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) top_model/main.cpp -o build/main_parking_lot.o

simulator: main_parking_lot.o
	$(CC) -g -o bin/PARKING_LOT build/main_parking_lot.o

#DEFAULT TARGET
all: simulator

#CLEAN COMMANDS
clean:
	rm -f bin/* build/*
