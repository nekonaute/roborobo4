//
// Created by pecoffet on 18/01/2021.
//

#include <pybind11/pybind11.h>
#include "contrib/pyroborobo/customModuleDefinitions.h"
#include "DistAware/include/pyroborobo/DistAwarePythonBindings.h"

void dummyCustomBindings(pybind11::module& m)
{

}

void addCustomBindings(pybind11::module &m)
{
    /* append your custom bindings in this function
     * dummyCustomBindings is given as an exemple
     */
    dummyCustomBindings(m);
    addDistAwareBindings(m);
}