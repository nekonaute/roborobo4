//
// Created by Paul Ecoffet on 17/02/2021.
//

#ifndef ROBOROBO3_WORLDOBSERVERTRAMPOLINE_H
#define ROBOROBO3_WORLDOBSERVERTRAMPOLINE_H



class WorldObserverTrampoline : public WorldObserver
{
public:
    using WorldObserver::WorldObserver;

    void initPre() override
    {
        PYBIND11_OVERLOAD_NAME(void, WorldObserver, "init_pre", initPre,);
    }

    void initPost() override
    {
        PYBIND11_OVERLOAD_NAME(void, WorldObserver, "init_post", initPost,);
    }

    void stepPre() override
    {
        PYBIND11_OVERLOAD_NAME(void, WorldObserver, "step_pre", stepPre,);
    }

    void stepPost() override
    {
        PYBIND11_OVERLOAD_NAME(void, WorldObserver, "step_post", stepPost,);
    }
};


template <class WOType> class PyWorldObserver : public WOType
{
public:
    using WOType::WOType;

    void initPre() override
    {
        PYBIND11_OVERLOAD_NAME(void, WOType, "init_pre", initPre,);
    }

    void initPost() override
    {
        PYBIND11_OVERLOAD_NAME(void, WOType, "init_post", initPost,);
    }

    void stepPre() override
    {
        PYBIND11_OVERLOAD_NAME(void, WOType, "step_pre", stepPre,);
    }

    void stepPost() override
    {
        PYBIND11_OVERLOAD_NAME(void, WOType, "step_post", stepPost,);
    }
};

#endif //ROBOROBO3_WORLDOBSERVERTRAMPOLINE_H
