//
// Created by Paul Ecoffet on 25/09/2020.
//

#ifndef ROBOROBO3_PYPHYSICALOBJECTFACTORY_H
#define ROBOROBO3_PYPHYSICALOBJECTFACTORY_H


#include <core/World/PhysicalObject.h>
#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class PyPhysicalObjectFactory
{
private:
    static std::map<std::string, py::handle> *objectConstructionDict;
    static std::vector<py::object> *objectList;


public:
    PyPhysicalObjectFactory() = delete;

    static void init();

    static void close();

    static std::shared_ptr<PhysicalObject> makeObject(const std::string &type, int id);

    static void updateObjectConstructionDict(const std::map<std::string, py::handle> &constructionDict);

    static py::dict getObjectData(int id);
};


#endif //ROBOROBO3_PYPHYSICALOBJECTFACTORY_H
