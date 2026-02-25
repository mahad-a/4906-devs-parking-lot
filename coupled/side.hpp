#ifndef __SIDE_HPP__
#define __SIDE_HPP__

#include <cadmium/modeling/devs/coupled.hpp>
#include "../atomics/sensor.hpp"

struct Side : public cadmium::Coupled {
    cadmium::Port<int> in;
    cadmium::Port<int> out;

    explicit Side(const std::string& id) : cadmium::Coupled(id) {
        in  = addInPort<int>("in");
        out = addOutPort<int>("out");

        auto sensor1         = addComponent<Sensor>("sensor1");
        auto sensor2         = addComponent<Sensor>("sensor2");
        auto side_aggregator = addComponent<Sensor>("side_aggregator");

        // both sensors receive the incoming signal
        addCoupling(in, sensor1->in);
        addCoupling(in, sensor2->in);

        // both sensors feed into the aggregator
        addCoupling(sensor1->out, side_aggregator->in);
        addCoupling(sensor2->out, side_aggregator->in);

        addCoupling(side_aggregator->out, out);
    }
};

#endif // __SIDE_HPP__
