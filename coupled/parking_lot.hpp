#ifndef __PARKING_LOT_HPP__
#define __PARKING_LOT_HPP__

#include <cadmium/modeling/devs/coupled.hpp>
#include "../atomics/screen.hpp"
#include "side.hpp"

struct ParkingLot : public cadmium::Coupled {
    cadmium::Port<int> in;
    cadmium::Port<int> out;

    explicit ParkingLot(const std::string& id) : cadmium::Coupled(id) {
        in  = addInPort<int>("in");
        out = addOutPort<int>("out");

        auto side_a = addComponent<Side>("side_a");
        auto side_b = addComponent<Side>("side_b");
        auto screen = addComponent<Screen>("screen");

        // broadcast arrival to both sides simultaneously
        addCoupling(in, side_a->in);
        addCoupling(in, side_b->in);

        // both sides report occupancy to the screen
        addCoupling(side_a->out, screen->in);
        addCoupling(side_b->out, screen->in);

        addCoupling(screen->out, out);
    }
};

#endif // __PARKING_LOT_HPP__
