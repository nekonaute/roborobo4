/*
 *  AgentObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 24/03/09.
 *  Copyright 2009. All rights reserved.
 *
 */

#include "Observers/AgentObserver.h"

AgentObserver::AgentObserver( )
{
}

AgentObserver::AgentObserver(std::shared_ptr<RobotWorldModel> __wm)
{
    _wm = __wm;
}

AgentObserver::~AgentObserver()
{
	// nothing to do.
}

void AgentObserver::reset()
{
	// nothing to do.
}

void AgentObserver::stepPre()
{
    // nothing to do.
}

void AgentObserver::stepPost()
{
    // through distance sensors
    for( int i = 0 ; i < _wm->_cameraSensorsNb; i++)
    {
        int targetIndex = _wm->getObjectIdFromCameraSensor(i);

        if ( targetIndex >= gPhysicalObjectIndexStartOffset && targetIndex < gRobotIndexStartOffset )   // sensor ray bumped into a physical object
        {
            targetIndex = targetIndex - gPhysicalObjectIndexStartOffset;
            //std::cout << "[DEBUG] Robot #" << _wm->getId() << " touched " << targetIndex << "\n";
            gPhysicalObjects[targetIndex]->isTouched(_wm->getId());
        }
    }

    // through floor sensor
    int targetIndex = _wm->getGroundSensorValue();
    if ( targetIndex >= gPhysicalObjectIndexStartOffset && targetIndex < gPhysicalObjectIndexStartOffset + (int)gPhysicalObjects.size() )   // ground sensor is upon a physical object (OR: on a place marked with this physical object footprint, cf. groundsensorvalues image)
    {
        targetIndex = targetIndex - gPhysicalObjectIndexStartOffset;
        //std::cout << "[DEBUG] #" << _wm->getId() << " walked upon " << targetIndex << "\n";
        gPhysicalObjects[targetIndex]->isWalked(_wm->getId());
    }
}

std::shared_ptr<Controller> AgentObserver::getController()
{
    return gWorld->getRobot(_wm->getId())->getController();
}
