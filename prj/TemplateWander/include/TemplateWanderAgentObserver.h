/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef TEMPLATEWANDERAGENTOBSERVER_H
#define TEMPLATEWANDERAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class TemplateWanderAgentObserver : public AgentObserver
{
public:
    using AgentObserver::AgentObserver;

    ~TemplateWanderAgentObserver();

    void reset() override;

    void stepPre() override;

};


#endif

