//
// Created by pecoffet on 15/10/2020.
//

#ifndef ROBOROBO3_AGENTOBSERVERTRAMPOLINE_H
#define ROBOROBO3_AGENTOBSERVERTRAMPOLINE_H

#include <core/Observers/AgentObserver.h>

class AgentObserverPublicist : public AgentObserver
{
public:
    using AgentObserver::_wm;
};

class AgentObserverTrampoline : public AgentObserver
{
public:
    using AgentObserver::AgentObserver;

    void reset() override
    {
        PYBIND11_OVERLOAD(void, AgentObserver, reset,);
    }

    void stepPre() override
    {
        PYBIND11_OVERLOAD_NAME(void, AgentObserver, "step_pre", stepPre,);
    }

    void stepPost() override
    {
        PYBIND11_OVERLOAD_NAME(void, AgentObserver, "step_post", stepPost,);
    }
};

template <class AGType> class PyAgentObserver : public AGType
{
public:
    using AGType::AGType;

    void reset() override
    {
        PYBIND11_OVERLOAD(void, AGType, reset,);
    }

    void stepPre() override
    {
        PYBIND11_OVERLOAD_NAME(void, AGType, "step_pre", stepPre,);
    }

    void stepPost() override
    {
        PYBIND11_OVERLOAD_NAME(void, AGType, "step_post", stepPost,);
    }
};

#endif //ROBOROBO3_AGENTOBSERVERTRAMPOLINE_H
