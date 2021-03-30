//
// Created by Paul Ecoffet on 25/09/2020.
//

#include "contrib/pyroborobo/ModuleDefinitions/pyRobotWorldModelModuleDefinition.h"
#include <pybind11/pybind11.h>
#include <core/WorldModels/RobotWorldModel.h>
#include <contrib/pyroborobo/RobotWorldModelTrampoline.h>
#include <Utilities/Geometry.h>

namespace py = pybind11;
using namespace pybind11::literals;

void addPyRobotWorldModelBinding(py::module &m)
{
    py::class_<sensor_array, std::shared_ptr<sensor_array>>(m, "sensor_array", py::buffer_protocol())
            .def_buffer([](sensor_array &s) {
                return py::buffer_info(
                        s.data(),
                        sizeof(double),
                        py::format_descriptor<double>::format(),
                        s.num_dimensions(),
                        {s.shape()[0], s.shape()[1]},
                        {s.strides()[0] * sizeof(double), s.strides()[1] * sizeof(double)},
                        true
                );
            });


    py::class_<RobotWorldModel, PyRobotWorldModel<>, std::shared_ptr<RobotWorldModel>>(m, "RobotWorldModel")
            .def(py::init<>())
            .def("reset", &RobotWorldModel::reset)
            .def("_get_max_dist_camera", [](RobotWorldModel &self) { return gSensorRange; })
            .def("_get_camera_sensors", [](RobotWorldModel &self) -> const sensor_array & {
                     return self._cameraSensors; /* super hack to make _cameraSensors public */
                 }, py::return_value_policy::reference,
                 R"doc(
Return the buffer view of the camera. Should not be called, use PyWorldModel.
)doc")
            .def_property("alive", &RobotWorldModel::isAlive, &RobotWorldModel::setAlive, R"doc(
bool: State if the robot is alive
)doc")
            .def_readwrite("translation", &RobotWorldModel::_desiredTranslationalValue, R"doc(
double: Robot's desired translation speed in pixels.
)doc")
            .def_readwrite("rotation", &RobotWorldModel::_desiredRotationalVelocity, R"doc(
double: Robot's desired rotation speed in degrees.
)doc")
            .def_readwrite("fitness", &RobotWorldModel::_fitnessValue, R"doc(
double: Robot's actual fitness
)doc")
            .def_property("absolute_orientation", [] (RobotWorldModel& self)
                {
                    return principalValue(self._agentAbsoluteOrientation, true);
                },
                [] (RobotWorldModel& self, double angle)
                {
                    self._agentAbsoluteOrientation = principalValue(angle, true);
                },
                R"doc(
double: Robot's absolute orientation in principal value (between (-180, 180]).
)doc")
            .def("_init_camera_sensors", &RobotWorldModel::initCameraSensors, "nbsensors"_a,
                 R"doc(
Prepare the new sensors, must call super

This method allow the preparation of the sensors properties. Look at
`~Pyroborobo.PyWorldModel` source for an example.
)doc");
}