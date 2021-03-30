//
// Created by pecoffet on 15/10/2020.
//

#include "contrib/pyroborobo/ModuleDefinitions/agentObserverModuleDefinition.h"
#include "contrib/pyroborobo/AgentObserverTrampoline.h"

namespace py = pybind11;
using namespace pybind11::literals;

void addAgentObserverBindings(pybind11::module &m)
{
    py::class_<AgentObserver, AgentObserverTrampoline, std::shared_ptr<AgentObserver> >(m, "AgentObserver")
            .def(py::init<std::shared_ptr<RobotWorldModel>>(), "world_model"_a)
            .def("reset", &AgentObserver::reset,
                 R"(
Reset the agent observer
)")
            .def("step_pre", &AgentObserver::stepPre,
                 R"doc(
Called at each timestep before the agent's controller.
)doc")
            .def("step_post", &AgentObserver::stepPost,
                 R"doc(
Called at each timestep after the agent's controller.
)doc")
            .def_property_readonly("controller", &AgentObserver::getController, "Controller: Controller associated with this AgentObserver")
            .def_readonly("world_model", &AgentObserverPublicist::_wm, "WorldModel: WorldModel associated with this AgentObserver");
}