//
// Created by Paul Ecoffet on 17/09/2020.
//

#ifndef ROBOROBO3_CIRCLEOBJECTTRAMPOLINE_H
#define ROBOROBO3_CIRCLEOBJECTTRAMPOLINE_H

#include <pybind11/pybind11.h>
#include "core/World/CircleObject.h"
#include <type_traits>


class CircleObjectPublicist : public CircleObject
{
public:
    using CircleObject::_radius;
    using CircleObject::_footprintRadius;

};

template<class BaseCircle = CircleObject>
class CircleObjectTrampoline : public BaseCircle
{
public:
    using BaseCircle::BaseCircle;

    CircleObjectTrampoline(int id, const pybind11::dict &data) : BaseCircle(id)
    {
        (void) data;
    }

    void step() override
    {
        PYBIND11_OVERLOAD_PURE(void, BaseCircle, step,);
    }

    bool canRegister() override
    {
        PYBIND11_OVERLOAD_NAME(bool, BaseCircle, "can_register", canRegister,);
    }

    void registerObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "register_object", registerObject,);
    }

    void unregisterObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "unregister_object", unregisterObject,);
    }

    void isTouched(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "is_touched", isTouched, _idAgent);
    }

    void isWalked(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "is_walked", isWalked, _idAgent);
    }

    void isPushed(int _id, std::tuple<double, double> _speed) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "is_pushed", isPushed, _id, _speed);
    }

    void show(SDL_Surface *surface) override
    {
        PYBIND11_OVERLOAD(void, BaseCircle, show, surface);
    }

    void hide() override
    {
        PYBIND11_OVERLOAD(void, BaseCircle, hide,);
    }

    void trueHide()
    {
        BaseCircle::_visible = false;
        hide();
    }

    void trueShow()
    {
        BaseCircle::_visible = true;
    }

    std::string inspect(std::string prefix) override
    {
        PYBIND11_OVERLOAD(std::string, BaseCircle, inspect, prefix);
    }

    void relocate() override
    {
        PYBIND11_OVERLOAD(void, BaseCircle, relocate,);
    }

    bool relocate(double x, double y) override
    {
        PYBIND11_OVERLOAD(bool, BaseCircle, relocate, x, y);
    }


};


template<class BaseCircle = CircleObject>
class PyCircleObject : public BaseCircle
{
public:
    using BaseCircle::BaseCircle;

    PyCircleObject(int id, const pybind11::dict &data) : BaseCircle(id)
    {
        (void) data;
    }

    void step() override
    {
        PYBIND11_OVERLOAD(void, BaseCircle, step,);
    }

    bool canRegister() override
    {
        PYBIND11_OVERLOAD_NAME(bool, BaseCircle, "can_register", canRegister,);
    }

    void registerObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "register_object", registerObject,);
    }

    void unregisterObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "unregister_object", unregisterObject,);
    }

    void isTouched(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "is_touched", isTouched, _idAgent);
    }

    void isWalked(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "is_walked", isWalked, _idAgent);
    }

    void isPushed(int _id, std::tuple<double, double> _speed) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseCircle, "is_pushed", isPushed, _id, _speed);
    }

    void show(SDL_Surface *surface) override
    {
        PYBIND11_OVERLOAD(void, BaseCircle, show, surface);
    }

    void hide() override
    {
        PYBIND11_OVERLOAD(void, BaseCircle, hide,);
    }

    void trueHide()
    {
        BaseCircle::_visible = false;
        hide();
    }

    void trueShow()
    {
        BaseCircle::_visible = true;
    }

    std::string inspect(std::string prefix) override
    {
        PYBIND11_OVERLOAD(std::string, BaseCircle, inspect, prefix);
    }

    void relocate() override
    {
        PYBIND11_OVERLOAD(void, BaseCircle, relocate,);
    }

    bool relocate(double x, double y) override
    {
        PYBIND11_OVERLOAD(bool, BaseCircle, relocate, x, y);
    }


};


#endif //ROBOROBO3_CIRCLEOBJECTTRAMPOLINE_H
