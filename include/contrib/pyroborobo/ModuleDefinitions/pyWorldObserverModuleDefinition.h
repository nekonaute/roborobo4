//
// Created by Paul Ecoffet on 25/09/2020.
//

#ifndef ROBOROBO3_PYWORLDOBSERVERMODULEDEFINITION_H
#define ROBOROBO3_PYWORLDOBSERVERMODULEDEFINITION_H

#include "pybind11/pybind11.h"
#include <pyroborobo/pyroborobocommon.h>


namespace py = pybind11;

void addPyWorldObserverBinding(py::module &m);


#endif //ROBOROBO3_PYWORLDOBSERVERMODULEDEFINITION_H
