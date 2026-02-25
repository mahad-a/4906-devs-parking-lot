#ifndef __PARKING_SYSTEM_HPP__
#define __PARKING_SYSTEM_HPP__

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include "../atomics/access_control.hpp"
#include "parking_lot.hpp"

struct ParkingSystem : public cadmium::Coupled {
    cadmium::Port<int> out;

    ParkingSystem(const std::string& id, const char* inputFilePath)
        : cadmium::Coupled(id) {
        out = addOutPort<int>("out");

        auto iestream         = addComponent<cadmium::lib::IEStream<int>>("iestream", inputFilePath);
        auto access_control_a = addComponent<AccessControl>("access_control_a");
        auto parking_lot      = addComponent<ParkingLot>("parking_lot");
        auto access_control_b = addComponent<AccessControl>("access_control_b");

        // entrance gate → lot → exit gate
        addCoupling(iestream->out, access_control_a->in);
        addCoupling(access_control_a->out, parking_lot->in);
        addCoupling(parking_lot->out, access_control_b->in);
        addCoupling(access_control_b->out, out);
    }
};

#endif // __PARKING_SYSTEM_HPP__
