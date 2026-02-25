#ifndef __ACCESS_CONTROL_HPP__
#define __ACCESS_CONTROL_HPP__

#include <cadmium/modeling/devs/atomic.hpp>
#include <limits>

struct AccessControlState {
    double sigma;
    // TODO: set initial state
    AccessControlState() : sigma(0) {}
};

std::ostream& operator<<(std::ostream& os, const AccessControlState& s) {
    os << s.sigma;
    return os;
}

// entrance or exit gate with a 5 second preparation delay
class AccessControl : public cadmium::Atomic<AccessControlState> {
public:
    cadmium::Port<int> in;
    cadmium::Port<int> out;

    explicit AccessControl(const std::string& id)
        : cadmium::Atomic<AccessControlState>(id, AccessControlState()) {
        in  = addInPort<int>("in");
        out = addOutPort<int>("out");
    }

    void externalTransition(AccessControlState& s, double e) const override {
        if (!in->getBag().empty()) {
            s.sigma = 5.0; // 5 second preparation delay
        }
    }

    void internalTransition(AccessControlState& s) const override {
        s.sigma = std::numeric_limits<double>::infinity();
    }

    void output(const AccessControlState& s) const override {
        out->addMessage(1);
    }

    [[nodiscard]] double timeAdvance(const AccessControlState& s) const override {
        return s.sigma;
    }
};

#endif // __ACCESS_CONTROL_HPP__
