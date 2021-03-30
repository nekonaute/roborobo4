/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef DISTAWAREAGENTOBSERVER_H
#define DISTAWAREAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class DistAwareAgentObserver : public AgentObserver
{
public:
    using AgentObserver::AgentObserver;

    ~DistAwareAgentObserver();

    void reset() override;

    void stepPre() override;

};


#endif

