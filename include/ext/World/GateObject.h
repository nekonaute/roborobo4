/*
 *  GateObject.h
 *  roborobo
 *
 *  Created by Nicolas on 26/4/2014.
 *
 */

#ifndef GATEOBJECT_H
#define GATEOBJECT_H

#include "World/SquareObject.h"

class GateObject : public SquareObject
{

private:

public :

    GateObject(int __id); // use PhysicalObjectFactory instead!
    virtual ~GateObject()
    {
    }

    void step() override;

    void isTouched(int __idAgent) override; // callback, triggered by agent
    void isWalked(int __idAgent) override; // callback, triggered by agent
    void
    isPushed(int __id, std::tuple<double, double> __speed) override; // callback, triggered by collision w/ agent/object
};

#endif
