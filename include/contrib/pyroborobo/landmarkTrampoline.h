//
// Created by Paul Ecoffet on 18/02/2021.
//

#ifndef ROBOROBO3_LANDMARKTRAMPOLINE_H
#define ROBOROBO3_LANDMARKTRAMPOLINE_H

class LandmarkTrampoline : public LandmarkObject
{
public:
    using LandmarkObject::LandmarkObject;

    void step() override
    {
        PYBIND11_OVERLOAD(void, LandmarkObject, step,);
    }
};

template <class LType> class PyLandmark : public LType
{
public:
    using LType::LType;

    void step() override
    {
        PYBIND11_OVERLOAD(void, LType, step,);
    }
};

#endif //ROBOROBO3_LANDMARKTRAMPOLINE_H
