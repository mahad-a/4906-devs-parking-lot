// experiment 6: parking lot — arrival fans to both sides, screen decrements count, 3s end-to-end delay

#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>

#include "../coupled/parking_lot.hpp"

#include <iostream>
#include <limits>
#include <memory>

struct ParkingLotExperiment : public cadmium::Coupled {
    ParkingLotExperiment(const std::string& id, const char* filePath)
        : cadmium::Coupled(id) {
        auto iestream    = addComponent<cadmium::lib::IEStream<int>>("iestream", filePath);
        auto parking_lot = addComponent<ParkingLot>("parking_lot");
        addCoupling(iestream->out, parking_lot->in);
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return -1;
    }
    auto model = std::make_shared<ParkingLotExperiment>("parking_lot_experiment", argv[1]);
    auto rc    = cadmium::RootCoordinator(model);
    rc.setLogger<cadmium::CSVLogger>("simulation_results/parking_lot_test.csv", ";");
    rc.start();
    rc.simulate(std::numeric_limits<double>::infinity());
    rc.stop();
    return 0;
}
