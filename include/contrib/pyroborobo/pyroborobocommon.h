//
// Created by Paul Ecoffet on 24/02/2021.
//

#ifndef ROBOROBO3_PYROBOROBOCOMMON_H
#define ROBOROBO3_PYROBOROBOCOMMON_H


#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <Controllers/Controller.h>
#include <World/PhysicalObject.h>
#include <World/LandmarkObject.h>
#include <WorldModels/RobotWorldModel.h>
#include <Agents/Robot.h>

PYBIND11_MAKE_OPAQUE(std::vector<py::object>);
PYBIND11_MAKE_OPAQUE(std::vector<py::handle>);





#endif //ROBOROBO3_PYROBOROBOCOMMON_H
