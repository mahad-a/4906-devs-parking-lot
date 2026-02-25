// experiment 3: screen — decrements available spaces on each arrival, 1s output delay

#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>

#include "../atomics/screen.hpp"

#include <iostream>
#include <limits>
#include <memory>

struct ScreenExperiment : public cadmium::Coupled {
    ScreenExperiment(const std::string& id, const char* filePath)
        : cadmium::Coupled(id) {
        auto iestream = addComponent<cadmium::lib::IEStream<int>>("iestream", filePath);
        auto screen   = addComponent<Screen>("screen");
        addCoupling(iestream->out, screen->in);
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return -1;
    }
    auto model = std::make_shared<ScreenExperiment>("screen_experiment", argv[1]);
    auto rc    = cadmium::RootCoordinator(model);
    rc.setLogger<cadmium::CSVLogger>("simulation_results/screen_test.csv", ";");
    rc.start();
    rc.simulate(std::numeric_limits<double>::infinity());
    rc.stop();
    return 0;
}
