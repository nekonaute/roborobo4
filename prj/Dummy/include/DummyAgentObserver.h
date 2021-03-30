/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef DUMMYAGENTOBSERVER_H
#define DUMMYAGENTOBSERVER_H

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class DummyAgentObserver : public AgentObserver
{
public:
    using AgentObserver::AgentObserver;

    void reset() override;

    void stepPre() override;
};

#endif

