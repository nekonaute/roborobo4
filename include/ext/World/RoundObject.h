/*
 *  RoundObject.h
 *  roborobo
 *
 *  Created by Nicolas on 25/4/2014.
 *
 */

#ifndef ROUNDOBJECT_H
#define ROUNDOBJECT_H

#include "World/CircleObject.h"

class RoundObject : public CircleObject
{
private:

public :

    RoundObject(int __id); // use PhysicalObjectFactory instead!
    ~RoundObject()
    {
    }

    void step() override;

    void isTouched(int __idAgent) override; // callback, triggered by agent
    void isWalked(int __idAgent) override; // callback, triggered by agent
    void isPushed(int __id, std::tuple<double, double> __speed) override; // callback, triggered by agent/object

};

#endif
