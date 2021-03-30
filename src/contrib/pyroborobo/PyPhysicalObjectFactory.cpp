//
// Created by Paul Ecoffet on 25/09/2020.
//

#include <string>
#include <core/RoboroboMain/roborobo.h>
#include "contrib/pyroborobo/PyPhysicalObjectFactory.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>

std::map<std::string, py::handle> *PyPhysicalObjectFactory::objectConstructionDict = nullptr; /* Might raise an exception that cannot be caught. */
std::vector<py::object> *PyPhysicalObjectFactory::objectList = nullptr;

std::shared_ptr<PhysicalObject> PyPhysicalObjectFactory::makeObject(const std::string &type, int id)
{
    std::shared_ptr<PhysicalObject> obj;

    if (objectConstructionDict == nullptr)
    {
        throw std::runtime_error("objectConstructorDict not initialised. Did you run Pyroborobo.create()?");
    }

    if (objectConstructionDict->find(type) != objectConstructionDict->end())
    {
        py::dict data = PyPhysicalObjectFactory::getObjectData(id);
        py::object pyobj = (*objectConstructionDict)[type](id, data);
        obj = pyobj.cast<std::shared_ptr<PhysicalObject> >();
        objectList->emplace_back(pyobj); /* Save the object ref to avoid unexpected gc from python */
    }
    else
    {
        throw std::runtime_error(
                std::string("this key '") + type + "' is not in the dict of physical object constructors");
    }
    return obj;
}

void PyPhysicalObjectFactory::updateObjectConstructionDict(const std::map<std::string, py::handle> &constructionDict)
{
    if (objectConstructionDict == nullptr)
    {
        throw std::runtime_error("objectConstructorDict not initialised. Did you run Pyroborobo.create()?");
    }
    for (const auto& keyval : constructionDict)
    {
        auto key = keyval.first;
        (*objectConstructionDict)[key] = keyval.second;
    }
}

py::dict PyPhysicalObjectFactory::getObjectData(int id)
{
    py::dict data;
    std::string test = std::string("physicalObject[") + std::to_string(id) + "].";
    for (const auto &keyval : gProperties)
    {
        const std::string &key = keyval.first;
        const std::string &val = keyval.second;
        if (boost::algorithm::starts_with(key, test))
        {
            std::string innerkey = key.substr(test.size());
            std::string lower_val = boost::to_lower_copy(val);
            bool success = true;
            if (lower_val == "true" || lower_val == "false")
            {
                data[py::str(innerkey)] = lower_val == "true";
            }
            else
            {
                size_t pos = 0;
                long integer_value = 0;
                try
                {
                    integer_value = std::stol(val, &pos);
                }
                catch (std::invalid_argument &e)
                {
                    success = false;
                }
                catch (std::out_of_range &e)
                {
                    success = false;
                }
                if (pos < val.size())
                {
                    success = false;
                }
                if (success)
                {
                    data[py::str(innerkey)] = integer_value;
                }
            }
            if (!success) /* If the conversion to an int has failed */
            {
                success = true;
                size_t pos = 0;
                double double_value = 0;
                try
                {
                    double_value = std::stod(val, &pos);
                }
                catch (std::invalid_argument &e)
                {
                    success = false;
                }
                catch (std::out_of_range &e)
                {
                    success = false;
                }
                if (pos < val.size())
                {
                    success = false;
                }
                if (success)
                {
                    data[py::str(innerkey)] = double_value;
                }
            }
            if (!success)
            {
                data[py::str(innerkey)] = val; /* insert value as string */
            }
        }
    }
    return data;
}

void PyPhysicalObjectFactory::init()
{
    if (objectList == nullptr)
    {
        objectList = new std::vector<py::object>;
    }
    if (objectConstructionDict == nullptr)
    {
        objectConstructionDict = new std::map<std::string, py::handle>;
    }
}

void PyPhysicalObjectFactory::close()
{
    delete objectList;
    objectList = nullptr;
    delete objectConstructionDict;
    objectConstructionDict = nullptr;
}
