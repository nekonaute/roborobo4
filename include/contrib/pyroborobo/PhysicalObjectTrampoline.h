//
// Created by pecoffet on 01/10/2020.
//

#ifndef ROBOROBO3_PHYSICALOBJECTTRAMPOLINE_H
#define ROBOROBO3_PHYSICALOBJECTTRAMPOLINE_H

#include <pybind11/pybind11.h>
#include <core/World/PhysicalObject.h>

class PhysicalObjectTrampoline : public PhysicalObject
{
public:
    using PhysicalObject::PhysicalObject;

    void step() override
    {
        PYBIND11_OVERLOAD_PURE(void, PhysicalObject, step,);
    }

    bool canRegister() override
    {
        PYBIND11_OVERLOAD_PURE(bool, PhysicalObject, canRegister,);
    } // test if register object is possible (use both shape or footprints)

    void registerObject() override
    {
        PYBIND11_OVERLOAD(void, PhysicalObject, registerObject,);
    } // register object in the world (write images) -- object-specific implementation. When implementing, call super class.

    void unregisterObject() override
    {
        PYBIND11_OVERLOAD_PURE_NAME(void, PhysicalObject, "unregister_object", unregisterObject,);
    } // unregister object in the world (write blank pixels)

    void isTouched(int _idAgent) override
    {
        PYBIND11_OVERLOAD_PURE_NAME(void, PhysicalObject, "is_touched", isTouched, _idAgent);
    }

    void isWalked(int _idAgent) override
    {
        PYBIND11_OVERLOAD_PURE_NAME(void, PhysicalObject, "is_walked", isWalked, _idAgent);
    }

    void isPushed(int _id, std::tuple<double, double> _speed) override
    {
        PYBIND11_OVERLOAD_PURE_NAME(void, PhysicalObject, "is_pushed", isPushed, _id, _speed);
    } // callback, triggered by agent

    void show(SDL_Surface *surface) override
    {
        PYBIND11_OVERLOAD_PURE(void, PhysicalObject, show, surface);
    }

    void hide() override
    {
        PYBIND11_OVERLOAD_PURE(void, PhysicalObject, hide);
    }
};

template <class POBase>
class PyPhysicalObject : public POBase
{
public:
    using POBase::POBase;

    void step() override
    {
        PYBIND11_OVERLOAD(void, POBase, step,);
    }

    bool canRegister() override
    {
        PYBIND11_OVERLOAD(bool, POBase, canRegister,);
    } // test if register object is possible (use both shape or footprints)

    void registerObject() override
    {
        PYBIND11_OVERLOAD(void, POBase, registerObject,);
    } // register object in the world (write images) -- object-specific implementation. When implementing, call super class.

    void unregisterObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, POBase, "unregister_object", unregisterObject,);
    } // unregister object in the world (write blank pixels)

    void isTouched(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, POBase, "is_touched", isTouched, _idAgent);
    }

    void isWalked(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, POBase, "is_walked", isWalked, _idAgent);
    }

    void isPushed(int _id, std::tuple<double, double> _speed) override
    {
        PYBIND11_OVERLOAD_NAME(void, POBase, "is_pushed", isPushed, _id, _speed);
    } // callback, triggered by agent

    void show(SDL_Surface *surface) override
    {
        PYBIND11_OVERLOAD(void, POBase, show, surface);
    }

    void hide() override
    {
        PYBIND11_OVERLOAD(void, POBase, hide);
    }
};


#endif //ROBOROBO3_PHYSICALOBJECTTRAMPOLINE_H
