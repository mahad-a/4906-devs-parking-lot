#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

#include <cadmium/modeling/devs/atomic.hpp>
#include <limits>

struct SensorState {
    double sigma;
    // TODO: set initial state
    SensorState() : sigma(0) {}
};

std::ostream& operator<<(std::ostream& os, const SensorState& s) {
    os << s.sigma;
    return os;
}

// parking space sensor with a 1 second preparation delay
// also used for side aggregators, which share the same behaviour
class Sensor : public cadmium::Atomic<SensorState> {
public:
    cadmium::Port<int> in;
    cadmium::Port<int> out;

    explicit Sensor(const std::string& id)
        : cadmium::Atomic<SensorState>(id, SensorState()) {
        in  = addInPort<int>("in");
        out = addOutPort<int>("out");
    }

    void externalTransition(SensorState& s, double e) const override {
        if (!in->getBag().empty()) {
            s.sigma = 1.0; // 1 second preparation delay
        }
    }

    void internalTransition(SensorState& s) const override {
        s.sigma = std::numeric_limits<double>::infinity();
    }

    void output(const SensorState& s) const override {
        out->addMessage(1);
    }

    [[nodiscard]] double timeAdvance(const SensorState& s) const override {
        return s.sigma;
    }
};

#endif // __SENSOR_HPP__
