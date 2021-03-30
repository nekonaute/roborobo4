//
// Created by pecoffet on 10/06/2020.
//

#ifndef ROBOROBO3_PYCONFIGURATIONLOADER_H
#define ROBOROBO3_PYCONFIGURATIONLOADER_H


#include <ext/Config/ConfigurationLoader.h>
#include <World/World.h>
#include <WorldModels/RobotWorldModel.h>
#include <Observers/WorldObserver.h>
#include <Observers/AgentObserver.h>
#include <Controllers/Controller.h>
#include <pybind11/pybind11.h>
#include <Dummy/include/DummyWorldObserver.h>
#include <Dummy/include/DummyAgentObserver.h>
#include <Dummy/include/DummyController.h>

#include <utility>

namespace py = pybind11;

class PyConfigurationLoader : public ConfigurationLoader
{
public:
    PyConfigurationLoader(ConfigurationLoader *configurationLoader, py::object worldObserverClass,
                          py::object agentControllerClass,
                          py::object worldModelClass, py::object agentObserverClass, Pyroborobo& pyrob)
            :
            fallbackconf(configurationLoader),
            worldObserverClass(std::move(worldObserverClass)),
            agentControllerClass(std::move(agentControllerClass)),
            worldModelClass(std::move(worldModelClass)),
            agentObserverClass(std::move(agentObserverClass)),
            pyroborobo(pyrob)
    {
    }

    ~PyConfigurationLoader() override
    {
        delete fallbackconf;
    }

    std::shared_ptr<WorldObserver> make_WorldObserver(World *w) override
    {
        py::object pyobj;
        std::shared_ptr<WorldObserver> cobj;
        if (worldObserverClass.is(py::none()))
        {
            cobj = fallbackconf->make_WorldObserver(w);
            pyobj = py::cast(cobj);
        }
        else if (py::isinstance<py::str>(worldObserverClass) && worldObserverClass.cast<std::string>() == "dummy")
        {
            cobj = std::make_shared<DummyWorldObserver>(w);
            pyobj = py::cast(cobj);
        }
        else
        {
            pyobj = worldObserverClass(w);
            cobj = pyobj.cast<std::shared_ptr<WorldObserver>>();
        }
        pyroborobo.setWorldObserver(pyobj);
        return cobj;
    }

    std::shared_ptr<RobotWorldModel> make_RobotWorldModel() override
    {
        py::object pyobj;
        std::shared_ptr<RobotWorldModel> cobj;
        if (worldModelClass.is(py::none()))
        {
            cobj = fallbackconf->make_RobotWorldModel();
            pyobj = py::cast(cobj);
        }
        else if (py::isinstance<py::str>(worldModelClass) && worldModelClass.cast<std::string>() == "dummy")
        {
            cobj = std::make_shared<RobotWorldModel>();
            pyobj = py::cast(cobj);
        }
        else
        {
            pyobj = worldModelClass();
            cobj = pyobj.cast<std::shared_ptr<RobotWorldModel>>();
        }
        pyroborobo.appendWorldModel(pyobj);
        return cobj;
    }

    std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm) override
    {
        std::shared_ptr<AgentObserver> cobj;
        py::object pyobj;
        if (agentObserverClass.is(py::none()))
        {
            cobj = fallbackconf->make_AgentObserver(wm);
            pyobj = py::cast(cobj);
        }
        else if (py::isinstance<py::str>(agentObserverClass) && agentObserverClass.cast<std::string>() == "dummy")
        {
            cobj = std::make_shared<DummyAgentObserver>(wm);
            pyobj = py::cast(cobj);
        }
        else
        {
            pyobj = agentObserverClass(wm);
            // allocated.push_back(py_agentobserver);
            cobj = pyobj.cast<std::shared_ptr<AgentObserver> >();
        }
        pyroborobo.appendAgentObserver(pyobj);
        return cobj;
    }

    std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm) override
    {
        std::shared_ptr<Controller> cobj;
        py::object pyobj;
        if (agentControllerClass.is(py::none()))
        {
            cobj = fallbackconf->make_Controller(wm);
            pyobj = py::cast(cobj);
        }
        else if (py::isinstance<py::str>(agentControllerClass) && agentControllerClass.cast<std::string>() == "dummy")
        {
            cobj = std::make_shared<DummyController>(wm);
            pyobj = py::cast(cobj);
        }
        else
        {
            pyobj = agentControllerClass(wm);
            // allocated.push_back(py_controller);
            cobj = pyobj.cast<std::shared_ptr<Controller>>();
        }
        pyroborobo.appendController(pyobj);
        return cobj;
    }

    std::shared_ptr<PhysicalObject> make_CustomObject(int id) override
    {
        return std::shared_ptr<PhysicalObject>(nullptr);
    }

private:

    ConfigurationLoader *fallbackconf;
    py::object worldObserverClass;
    py::object agentControllerClass;
    py::object worldModelClass;
    py::object agentObserverClass;
    Pyroborobo &pyroborobo;
};


#endif //ROBOROBO3_PYCONFIGURATIONLOADER_H
