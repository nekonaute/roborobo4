//
// Created by Paul Ecoffet on 08/06/2020.
//

#ifndef ROBOROBO3_CONTROLLERTRAMPOLINE_H
#define ROBOROBO3_CONTROLLERTRAMPOLINE_H

#include "WorldModels/RobotWorldModel.h"
#include "Controllers/Controller.h"
#include "RoboroboMain/main.h"
#include "RoboroboMain/roborobo.h"
#include <csignal>
#include <pybind11/pybind11.h>
#include "contrib/pyroborobo/pyroborobo.h"

class ControllerTrampoline : public Controller
{
public:
    /* Inherit the constructors */
    using Controller::Controller;

    /* Trampoline (need one for each virtual function) */
    void step() override
    {
        PYBIND11_OVERLOAD_PURE(
                void, /* Return type */
                Controller,      /* Parent class */
                step,          /* Name of function in C++ (must match Python name) */
        );
    }

    void reset() override
    {
        PYBIND11_OVERLOAD_PURE(
                void, /* Return type */
                Controller,      /* Parent class */
                reset,          /* Name of function in C++ (must match Python name) */
        );
    }

    std::string inspect(std::string prefix = "") override
    {
        PYBIND11_OVERLOAD(
                std::string, /* Return type */
                Controller,      /* Parent class */
                inspect,          /* Name of function in C++ (must match Python name) */
                prefix
        );
    }


};


template<class ControllerType = Controller>
class PyController : public ControllerType
{
public:
    /* Inherit the constructors */
    using ControllerType::ControllerType;

    /* Trampoline (need one for each virtual function) */
    void step() override
    {
        PYBIND11_OVERLOAD(
                void, /* Return type */
                ControllerType,      /* Parent class */
                step,          /* Name of function in C++ (must match Python name) */
        );
    }

    void reset() override
    {
        PYBIND11_OVERLOAD(
                void, /* Return type */
                ControllerType,      /* Parent class */
                reset,          /* Name of function in C++ (must match Python name) */
        );
    }

    std::string inspect(std::string prefix = "") override
    {
        PYBIND11_OVERLOAD(
                std::string, /* Return type */
                ControllerType,      /* Parent class */
                inspect,          /* Name of function in C++ (must match Python name) */
                prefix
        );
    }


};

#endif //ROBOROBO3_CONTROLLERTRAMPOLINE_H
