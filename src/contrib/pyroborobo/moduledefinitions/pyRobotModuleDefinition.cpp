//
// Created by Paul Ecoffet on 25/09/2020.
//

#include <pybind11/pybind11.h>
#include <contrib/pyroborobo/ModuleDefinitions/pyRobotModuleDefinition.h>
#include <core/Agents/Robot.h>
#include <core/RoboroboMain/roborobo.h>
#include <core/Controllers/Controller.h>
#include <core/Observers/AgentObserver.h>
#include <core/WorldModels/RobotWorldModel.h>

namespace py = pybind11;
using namespace pybind11::literals;

void addPyRobotBinding(py::module &m)
{
    py::class_<Robot, std::shared_ptr<Robot>>(m, "Robot")
            .def("set_position", [](Robot &self, double x, double y, bool register_=true, bool force=false) {
                bool success = true;
                if (register_)
                {
                    self.unregisterRobot();
                }
                int x_prev, y_prev;
                self.getCoord(x_prev, y_prev);
                self.setCoord(x, y);
                self.setCoordReal(x, y);
                if (!force && self.isCollision())
                {
                    self.setCoord(x_prev, y_prev);
                    self.setCoordReal(x_prev, y_prev);
                    success = false;
                }
                if (register_)
                {
                    self.registerRobot();
                }
                return success;
            }, "x"_a, "y"_a, "register"_a = true, "force"_a = true,
                 "set the robot at the position (x, y). if `register` then the "
                 "function take care of the registration. if `force` is true, the function ignore collisions.")
            .def("set_absolute_orientation", [] (Robot &self, double angle) {
                self.getWorldModel()->_agentAbsoluteOrientation = angle;
            })
            .def("find_random_location", [](Robot &self) {
                int x, y;
                self.unregisterRobot();
                std::tie(x, y) = self.findRandomLocation(gLocationFinderMaxNbOfTrials);
                self.setCoord(x, y);
                self.setCoordReal(x, y);
                self.registerRobot();
            }, "Place the robot at a random location")
            .def("register", &Robot::registerRobot, "Add the robot from the simulation")
            .def("unregister", &Robot::unregisterRobot, "Remove the robot from the simulation")
            .def_property_readonly("controller", &Robot::getController, "PyController: The robot's controller")
            .def_property_readonly("position", [] (Robot& self) -> std::tuple<double, double> {
                const auto pos = self.getController()->getPosition();
                return {pos.x, pos.y};
            })
            .def_property_readonly("observer", &Robot::getObserver, "PyAgentObserver: The robot's agent observer")
            .def_property_readonly("world_model", &Robot::getWorldModel, "RobotWorldModel: The robot's world model");
}
