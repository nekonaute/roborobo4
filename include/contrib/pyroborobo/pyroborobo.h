#ifndef _PYROBOROBO_DEF_H_
#define _PYROBOROBO_DEF_H_

#include "pyroborobocommon.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <Agents/Robot.h>
#include <World/World.h>
#include <Observers/WorldObserver.h>
#include <Observers/AgentObserver.h>
#include <WorldModels/RobotWorldModel.h>
#include <Controllers/Controller.h>
#include <Utilities/Timer.h>
#include <Agents/InspectorAgent.h>

namespace py = pybind11;
using namespace pybind11::literals;

class Pyroborobo
{
public:

    static std::shared_ptr<Pyroborobo> createRoborobo(const std::string &properties_file,
                                      py::object worldObserverClass,
                                      py::object agentControllerClass,
                                      py::object worldModelClass,
                                      py::object agentObserverClass,
                                      py::dict objectClassDict,
                                      const py::dict options);

    ~Pyroborobo();

    static std::shared_ptr<Pyroborobo> get();

    void start();

    bool update(size_t n_step = 1);

    py::object addObjectToEnv(py::object obj);

    const std::vector<py::object> & getControllers() const;

    const std::vector<py::object> & getWorldModels() const;

    const std::vector<py::object> & getAgentObservers() const;

    py::object getWorldObserver()
    {
        if (!initialized)
        {
            throw std::runtime_error("World Observer has not been instantiated yet. Have you called roborobo.start()?");
        }
        return pywobs;
    }

    const std::vector<py::object>& getObjects() const;

    void close();
    void _gatherProjectInstances();

    Pyroborobo(const std::string &properties_file,
               py::object worldObserverClass,
               py::object agentControllerClass,
               py::object worldModelClass,
               py::object agentObserverClass,
               py::dict objectClassDict,
               const py::dict options);


    void setWorldObserver(py::object object);

    void appendWorldModel(py::object pywm);

    void appendAgentObserver(py::object pyao);

    void appendController(py::object pyctl);

private:

    static std::shared_ptr<Pyroborobo> instance;




    void overrideProperties(const py::dict dict);

    void initCustomConfigurationLoader(py::object worldObserverClass,
                                       py::object agentControllerClass,
                                       py::object worldModelClass,
                                       py::object agentObserverClass);

    Timer fps;
    World *world = nullptr;
    long long currentIt = 0;
    bool initialized = false;
    std::vector<py::object > controllers;
    std::vector<py::object > worldmodels;
    std::vector<py::object > agentobservers;
    std::vector<py::object > objects;
    std::vector<py::object > landmarks;
    std::shared_ptr<WorldObserver> wobs;
    py::object pywobs;
    py::object worldObserverClass;
    py::object agentControllerClass;
    py::object worldModelClass;
    py::object agentObserverClass;
    std::map<std::string, py::handle> objectClassDict;
};

#endif