/*
 *  SwitchObject.h
 *  roborobo
 *
 *  Created by Nicolas on 25/4/2014.
 *
 */

#ifndef SWITCHOBJECT_H
#define SWITCHOBJECT_H

#include "World/CircleObject.h"

class SwitchObject : public CircleObject
{

private:
    int sendMessageTo;

public :

    explicit SwitchObject(int _id); // use PhysicalObjectFactory instead!
    ~SwitchObject() = default;

    void step() override;

    void isTouched(int _idAgent) override; // callback, triggered by agent
    void isWalked(int _idAgent) override; // callback, triggered by agent
    void
    isPushed(int _id, std::tuple<double, double> _speed) override; // callback, triggered by collision w/ agent/object
};

#endif
