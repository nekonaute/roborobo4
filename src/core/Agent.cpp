/*
 *  agent.cpp
 *  roborobo
 *
 *  Created by Nicolas on 16/12/08.
 *  Copyright 2008. All rights reserved.
 *
 */

#include "Agents/Agent.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/Graphics.h"

Agent::Agent()
{
	// dont forget to call your own init() method
}


void Agent::getCoord(int &coord_x, int &coord_y)
{
    coord_x=_x;
    coord_y=_y;
}

void Agent::updateCoord(int &__xUpdate, int &__yUpdate)
{
    _x += __xUpdate;
    _y += __yUpdate;
}

void Agent::setCoord (int __x, int __y) // agent is centered on point
{
    _x = __x - gRobotWidth/2 ;
    _y = __y - gRobotHeight/2 ;
}

/**
    * Display agent on screen. Add information caption if needed.
	* (render mode only) 
    */
void Agent::show(SDL_Surface *surface) // display on screen -- method may be overriden
{
    //Show the dot
    apply_surface( _x - gCamera.x, _y - gCamera.y, gRobotDisplayImage, surface );
}

 /**
    * update the agent position in the environment. E.g. Move and apply simple physics (ie. obstacle collision detection and consequences).
    */
void Agent::move(int recursiveIt)
{
    // not implemented -- check Robot::move(...)
}


/* position camera */
void Agent::set_camera()
{
    //Center the camera over the dot
    gCamera.x = ( _x + gRobotWidth / 2 ) - gArenaWidth / 2;
    gCamera.y = ( _y + gRobotHeight / 2 ) - gArenaHeight / 2;
    
    //Keep the camera in bounds.
    if( gCamera.x < 0 )        gCamera.x = 0;    
    if( gCamera.y < 0 )        gCamera.y = 0;    
    if( gCamera.x > gAreaWidth  - gCamera.w )        gCamera.x = gAreaWidth - gCamera.w;    
    if( gCamera.y > gAreaHeight - gCamera.h )        gCamera.y = gAreaHeight - gCamera.h;
}

bool Agent::isInstanceOf ( int index ) // static
{
    if ( index >= gRobotIndexStartOffset && index < gRobotIndexStartOffset+gNbOfRobots )
        return true;
    else
        return false;
}





