// experiment 2: access control b — exit gate, same 5s delay, different input stimulus

#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>

#include "../atomics/access_control.hpp"

#include <iostream>
#include <limits>
#include <memory>

struct AccessControlBExperiment : public cadmium::Coupled {
    AccessControlBExperiment(const std::string& id, const char* filePath)
        : cadmium::Coupled(id) {
        auto iestream        = addComponent<cadmium::lib::IEStream<int>>("iestream", filePath);
        auto access_control  = addComponent<AccessControl>("access_control_b");
        addCoupling(iestream->out, access_control->in);
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return -1;
    }
    auto model = std::make_shared<AccessControlBExperiment>("ac_b_experiment", argv[1]);
    auto rc    = cadmium::RootCoordinator(model);
    rc.setLogger<cadmium::CSVLogger>("simulation_results/access_control_b_test.csv", ";");
    rc.start();
    rc.simulate(std::numeric_limits<double>::infinity());
    rc.stop();
    return 0;
}
