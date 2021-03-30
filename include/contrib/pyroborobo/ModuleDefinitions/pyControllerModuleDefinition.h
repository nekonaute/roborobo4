//
// Created by Paul Ecoffet on 25/09/2020.
//

#ifndef ROBOROBO3_PYCONTROLLERMODULEDEFINITION_H
#define ROBOROBO3_PYCONTROLLERMODULEDEFINITION_H

#include <pybind11/pybind11.h>
#include <pyroborobo/pyroborobocommon.h>


void addPyControllerBinding(pybind11::module &m);


#endif //ROBOROBO3_PYCONTROLLERMODULEDEFINITION_H
