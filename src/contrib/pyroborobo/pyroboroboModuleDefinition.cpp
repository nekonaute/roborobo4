#include <pybind11/pybind11.h>
#include <pyroborobo/pyroborobo.h>
#include <core/Controllers/Controller.h>
#include <core/WorldModels/RobotWorldModel.h>
#include <core/Observers/WorldObserver.h>
#include <core/World/World.h>
#include <core/Agents/Robot.h>
#include <core/RoboroboMain/roborobo.h>
#include <contrib/pyroborobo/ModuleDefinitions/pyRobotWorldModelModuleDefinition.h>
#include <contrib/pyroborobo/ModuleDefinitions/pyRobotModuleDefinition.h>
#include <contrib/pyroborobo/ModuleDefinitions/pyObjectsModuleDefinition.h>
#include <pyroborobo/ModuleDefinitions/landmarkModuleDefinition.h>
#include <pyroborobo/RobotWorldModelTrampoline.h>
#include "contrib/pyroborobo/ModuleDefinitions/pyWorldObserverModuleDefinition.h"
#include "contrib/pyroborobo/ModuleDefinitions/pyControllerModuleDefinition.h"
#include "contrib/pyroborobo/ModuleDefinitions/pyRoboroboModuleDefinition.h"
#include "contrib/pyroborobo/ModuleDefinitions/agentObserverModuleDefinition.h"
#include "contrib/pyroborobo/customModuleDefinitions.h"

namespace py = pybind11;
using namespace pybind11::literals;


PYBIND11_MODULE(pyroborobo, m)
{
    py::options op;
    py::class_<SDL_Surface>(m, "RoboroboSurface", py::buffer_protocol())
            .def_buffer([](SDL_Surface &m) -> py::buffer_info {
                auto* fmt=m.format;

                /* Check the bitdepth of the surface */
                if(fmt->BitsPerPixel!=32){
                    throw std::runtime_error("Invalid RGBA surface for casting to numpy");
                }

                return py::buffer_info(
                        m.pixels,                               /* Pointer to buffer */
                        sizeof(uint8_t),                          /* Size of one scalar */
                        py::format_descriptor<uint8_t>::format(), /* Python struct-style format descriptor */
                        3,                                      /* Number of dimensions */
                        { m.h, m.w, 4 }, /* Buffer dimensions */
                        { sizeof(uint8_t) * 4 * m.w,
                          sizeof(uint8_t) * 4,
                          sizeof(uint8_t) /* Strides (in bytes) for each index */
                        },
                        true
                );
            });
    //op.disable_function_signatures();
    //m.attr("__name__") = "pyroborobo";
    addPyRoboroboBinding(m);
    addPyControllerBinding(m);
    //addPyRobotWorldModelBinding(m);
    addPyWorldObserverBinding(m);
    py::class_<RobotWorldModel, PyRobotWorldModel<>, std::shared_ptr<RobotWorldModel>>(m, "WorldModel");
    py::class_<World, std::shared_ptr<World>> (m, "World");
    py::class_<Robot, std::shared_ptr<Robot>>(m, "Robot");
    //addPyRobotBinding(m);
    addPyObjectsBindings(m);
    addAgentObserverBindings(m);
    addLandmarkBindings(m);
    addCustomBindings(m);

}
