// experiment 5: side b — same structure as side a, different input timing

#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>

#include "../coupled/side.hpp"

#include <iostream>
#include <limits>
#include <memory>

struct SideBExperiment : public cadmium::Coupled {
    SideBExperiment(const std::string& id, const char* filePath)
        : cadmium::Coupled(id) {
        auto iestream = addComponent<cadmium::lib::IEStream<int>>("iestream", filePath);
        auto side_b   = addComponent<Side>("side_b");
        addCoupling(iestream->out, side_b->in);
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return -1;
    }
    auto model = std::make_shared<SideBExperiment>("side_b_experiment", argv[1]);
    auto rc    = cadmium::RootCoordinator(model);
    rc.setLogger<cadmium::CSVLogger>("simulation_results/side_b_test.csv", ";");
    rc.start();
    rc.simulate(std::numeric_limits<double>::infinity());
    rc.stop();
    return 0;
}
