/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef TEMPLATEEEAGENTOBSERVER_H
#define TEMPLATEEEAGENTOBSERVER_H

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class TemplateEEAgentObserver : public AgentObserver
{
public:
    using AgentObserver::AgentObserver;

    ~TemplateEEAgentObserver() override;

    void reset() override;

    void stepPre() override;

};

#endif
