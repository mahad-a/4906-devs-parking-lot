#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <cadmium/modeling/devs/atomic.hpp>
#include <limits>

struct ScreenState {
    double sigma;
    int    count; // available parking spaces

    // TODO: set initial state
    ScreenState() : sigma(0), count(50) {} // 50 spaces on startup
};

std::ostream& operator<<(std::ostream& os, const ScreenState& s) {
    os << "available_spaces:" << s.count;
    return os;
}

// tracks and displays available spaces, decrementing on each car arrival
class Screen : public cadmium::Atomic<ScreenState> {
public:
    cadmium::Port<int> in;
    cadmium::Port<int> out;

    explicit Screen(const std::string& id)
        : cadmium::Atomic<ScreenState>(id, ScreenState()) {
        in  = addInPort<int>("in");
        out = addOutPort<int>("out");
    }

    void externalTransition(ScreenState& s, double e) const override {
        if (!in->getBag().empty()) {
            s.count--;
            s.sigma = 1.0; // 1 second preparation delay
        }
    }

    void internalTransition(ScreenState& s) const override {
        s.sigma = std::numeric_limits<double>::infinity();
    }

    // sends the trigger signal followed by the current space count
    void output(const ScreenState& s) const override {
        out->addMessage(1);
        out->addMessage(s.count);
    }

    [[nodiscard]] double timeAdvance(const ScreenState& s) const override {
        return s.sigma;
    }
};

#endif // __SCREEN_HPP__
