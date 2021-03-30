//
// Created by pecoffet on 18/01/2021.
//

#include "DistAware/include/pyroborobo/DistAwarePythonBindings.h"
#include "DistAware/include/DistAwareController.h"
#include "WorldModels/RobotWorldModel.h"
#include "contrib/pyroborobo/ControllerTrampoline.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;


void addDistAwareBindings(py::module& m)
{
    auto distcont = py::class_<DistAwareController, Controller, PyController<DistAwareController>, std::shared_ptr<DistAwareController> >(
            m, "DistAwareController");
    distcont.def(py::init<std::shared_ptr<RobotWorldModel>>(), "world_model"_a, "");
    distcont.def("get_distance_to_robot", &DistAwareController::distanceToRobot, "id"_a, R"doc(float: The distance to the robot of id ``id``.)doc");
}