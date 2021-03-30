/*
 *  AgentObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 24/03/09.
 *  Copyright 2009. All rights reserved.
 *
 */

 
#ifndef AGENTOBSERVER_H
#define AGENTOBSERVER_H 

#include "Observers/Observer.h"
#include "Controllers/Controller.h"

#include "World/World.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"

class RobotWorldModel;

class AgentObserver : public Observer
{
protected:
    std::shared_ptr<RobotWorldModel> _wm;

public:
    AgentObserver();

    AgentObserver(std::shared_ptr<RobotWorldModel> __wm);

    ~AgentObserver();

    virtual void reset();

    std::shared_ptr<Controller> getController();

    void stepPre() override;

    void stepPost() override;

};


#endif

