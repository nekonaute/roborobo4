//
// Created by Paul Ecoffet on 25/09/2020.
//

#include <contrib/pyroborobo/SquareObjectTrampoline.h>
#include <contrib/pyroborobo/CircleObjectTrampoline.h>
#include <core/RoboroboMain/roborobo.h>
#include <contrib/pyroborobo/ControllerTrampoline.h>
#include <contrib/pyroborobo/RobotWorldModelTrampoline.h>
#include <core/Agents/Robot.h>
#include <core/World/World.h>
#include <core/Observers/WorldObserver.h>
#include <core/WorldModels/RobotWorldModel.h>
#include <core/Controllers/Controller.h>
#include <pyroborobo/pyroborobo.h>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include "contrib/pyroborobo/ModuleDefinitions/pyWorldObserverModuleDefinition.h"
#include "contrib/pyroborobo/WorldObserverTrampoline.h"


void addPyWorldObserverBinding(py::module &m)
{
    pybind11::class_<WorldObserver, WorldObserverTrampoline, std::shared_ptr<WorldObserver>>(m, "WorldObserver")
            .def(py::init<World *>(), "World"_a, py::return_value_policy::reference,
                 R"doc()doc")
            .def("init_pre", &WorldObserver::initPre, R"doc(Called before initialising robots & objects.)doc")
            .def("init_post", &WorldObserver::initPost, R"doc(Called after initialising robots & objects.)doc")
            .def("step_pre", &WorldObserver::stepPre, R"doc(
Call at each time step before the steps of objects and robots
)doc")
            .def("step_post", &WorldObserver::stepPost, R"doc(
Call at each time step after the steps of objects and robots
)doc");
}