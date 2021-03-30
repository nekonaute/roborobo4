//
// Created by Paul Ecoffet on 25/09/2020.
//

#ifndef ROBOROBO3_PYOBJECTSMODULEDEFINITION_H
#define ROBOROBO3_PYOBJECTSMODULEDEFINITION_H

#include <pybind11/pybind11.h>
#include <pyroborobo/pyroborobocommon.h>


void addPyObjectsBindings(pybind11::module &m);

#endif //ROBOROBO3_PYOBJECTSMODULEDEFINITION_H
