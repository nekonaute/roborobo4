//
// Created by Paul Ecoffet on 25/09/2020.
//

#ifndef ROBOROBO3_SQUAREOBJECTTRAMPOLINE_H
#define ROBOROBO3_SQUAREOBJECTTRAMPOLINE_H

#include <core/World/SquareObject.h>
#include <pybind11/pybind11.h>


class SquareObjectPublicist : public SquareObject
{
public:
    using SquareObject::_soft_w;
    using SquareObject::_soft_h;
    using SquareObject::_solid_w;
    using SquareObject::_solid_h;
};

template<class BaseSquare = SquareObject>
class SquareObjectTrampoline : public BaseSquare
{
public:
    using BaseSquare::BaseSquare;

    SquareObjectTrampoline(int id, const pybind11::dict &data) : BaseSquare(id)
    {
        (void) data;
    };

    void step() override
    {
        PYBIND11_OVERLOAD(void, BaseSquare, step,);
    }

    bool canRegister() override
    {
        PYBIND11_OVERLOAD_NAME(bool, BaseSquare, "can_register", canRegister,);
    }

    void registerObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "register", registerObject,);
    }

    void unregisterObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "unregister", unregisterObject,);
    }

    void isTouched(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "is_touched", isTouched, _idAgent);
    }

    void isWalked(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "is_walked", isWalked, _idAgent);
    }

    void isPushed(int _id, std::tuple<double, double> _speed) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "is_pushed", isPushed, _id, _speed);
    }

    void show(SDL_Surface *surface) override
    {
        PYBIND11_OVERLOAD(void, BaseSquare, show, surface);
    }

    void hide() override
    {
        PYBIND11_OVERLOAD(void, BaseSquare, hide,);
    }

    std::string inspect(std::string prefix) override
    {
        PYBIND11_OVERLOAD(std::string, BaseSquare, inspect, prefix);
    }

    void relocate() override
    {
        PYBIND11_OVERLOAD(void, BaseSquare, relocate,);
    }

    bool relocate(double x, double y) override
    {
        PYBIND11_OVERLOAD(bool, BaseSquare, relocate, x, y);
    }

    void trueHide()
    {
        BaseSquare::_visible = false;
        hide();
    }

    void trueShow()
    {
        BaseSquare::_visible = true;
        show(gScreen);
    }

};

template<class BaseSquare = SquareObject>
class PySquareObject : public BaseSquare
{
public:
    using BaseSquare::BaseSquare;

    PySquareObject(int id, const pybind11::dict &data) : BaseSquare(id)
    {
        (void) data;
    };

    void step() override
    {
        PYBIND11_OVERLOAD(void, BaseSquare, step,);
    }

    bool canRegister() override
    {
        PYBIND11_OVERLOAD_NAME(bool, BaseSquare, "can_register", canRegister,);
    }

    void registerObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "register", registerObject,);
    }

    void unregisterObject() override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "unregister", unregisterObject,);
    }

    void isTouched(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "is_touched", isTouched, _idAgent);
    }

    void isWalked(int _idAgent) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "is_walked", isWalked, _idAgent);
    }

    void isPushed(int _id, std::tuple<double, double> _speed) override
    {
        PYBIND11_OVERLOAD_NAME(void, BaseSquare, "is_pushed", isPushed, _id, _speed);
    }

    void show(SDL_Surface *surface) override
    {
        PYBIND11_OVERLOAD(void, BaseSquare, show, surface);
    }

    void hide() override
    {
        PYBIND11_OVERLOAD(void, BaseSquare, hide,);
    }

    std::string inspect(std::string prefix) override
    {
        PYBIND11_OVERLOAD(std::string, BaseSquare, inspect, prefix);
    }

    void relocate() override
    {
        PYBIND11_OVERLOAD(void, BaseSquare, relocate,);
    }

    bool relocate(double x, double y) override
    {
        PYBIND11_OVERLOAD(bool, BaseSquare, relocate, x, y);
    }

    void trueHide()
    {
        BaseSquare::_visible = false;
        hide();
    }

    void trueShow()
    {
        BaseSquare::_visible = true;
    }

};


#endif //ROBOROBO3_SQUAREOBJECTTRAMPOLINE_H
