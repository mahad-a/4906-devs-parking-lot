#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <iostream>
#include <limits>
#include <memory>
#include "../coupled/parking_system.hpp"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_input_file>" << std::endl;
        return -1;
    }

    const char* inputFilePath = argv[1];

    auto model = std::make_shared<ParkingSystem>("parking_system", inputFilePath);

    auto rootCoordinator = cadmium::RootCoordinator(model);
    rootCoordinator.setLogger<cadmium::CSVLogger>(
        "simulation_results/parking_system_test.csv", ";");

    rootCoordinator.start();
    rootCoordinator.simulate(std::numeric_limits<double>::infinity());
    rootCoordinator.stop();

    return 0;
}
