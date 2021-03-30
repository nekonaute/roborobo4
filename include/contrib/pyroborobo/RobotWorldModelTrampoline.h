//
// Created by Paul Ecoffet on 08/06/2020.
//

#ifndef ROBOROBO3_ROBOTWORLDMODELTRAMPOLINE_H
#define ROBOROBO3_ROBOTWORLDMODELTRAMPOLINE_H

#include "WorldModels/RobotWorldModel.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;

template <class RWMBase = RobotWorldModel>
class PyRobotWorldModel : public RWMBase
{
protected:
    static_assert(std::is_base_of<RobotWorldModel, RWMBase>::value, "RWMBase not derived from RobotWorldModel");
public:
    using RWMBase::RWMBase;

    void reset() override
    {
        PYBIND11_OVERLOAD(void, RWMBase, reset,);
    }

    void initCameraSensors(int nbsensors) override
    {
        PYBIND11_OVERLOAD_NAME(void, RWMBase, "_init_camera_sensors", initCameraSensors, nbsensors);
    }

};

#endif //ROBOROBO3_ROBOTWORLDMODELTRAMPOLINE_H
