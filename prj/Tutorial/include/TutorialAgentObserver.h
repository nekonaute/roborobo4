/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef TUTORIALAGENTOBSERVER_H
#define TUTORIALAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class TutorialAgentObserver : public AgentObserver
{
public:
    using AgentObserver::AgentObserver;

    ~TutorialAgentObserver();

    void reset() override;

    void stepPre() override;

};


#endif

