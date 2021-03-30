/*
 *  CircleObject.h
 *  roborobo
 *
 *  Created by Nicolas on 25/4/2014.
 *
 */

#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "World/PhysicalObject.h"

class CircleObject : public PhysicalObject
{

protected:

    double _radius; // radius. In pixels.
    double _footprintRadius;
public:
    double getFootprintRadius() const;

    void setFootprintRadius(double footprintRadius, bool force = false);
    double getRadius() const;

    void setRadius(double radius, bool force = false);
    // radius of footprint, accessible to ground sensors. In pixels.

public :

    explicit CircleObject(int _id); // use PhysicalObjectFactory instead!
    ~CircleObject()
    = default;

    bool canRegister() override; // test if register object is possible (use both shape or footprints)
    void registerObject() override; // register object in the world (write images)
    void unregisterObject() override; // unregister object in the world (write blank pixels)
    void show(SDL_Surface *surface) override; // wrt. screen-rendering
    void hide() override;    // wrt. screen-rendering
    void step() override;

    /* add default behavior for callbacks */

    void isTouched(int _id) override
    {};

    void isWalked(int _id) override
    {};

    void isPushed(int _id, std::tuple<double, double> _speed) override
    {};

    std::string inspect(std::string prefix="") override
    {
        std::stringstream stream;
        stream << "[INFO] SquareObject with id" << getId() << "\n";
        stream << "Override inspect to display your own info\n";
        return stream.str();
    }
};

#endif
