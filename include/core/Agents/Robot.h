/*
 *  Robot.h
 *  roborobo
 *
 *  Created by Nicolas on 17/12/08.
 *  Copyright 2008. All rights reserved.
 *
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Agents/Agent.h"

class World;
class Controller;
class AgentObserver;
class RobotWorldModel;
class WorldObserver;

class Robot : public Agent
{

private:

    std::shared_ptr<Controller> _controller;
    std::shared_ptr<AgentObserver> _agentObserver;

    std::shared_ptr<RobotWorldModel> _wm;

    // real displacement (x/y format, delta applied to real coordinates (_xReal,_yReal))
    double _xDeltaReal;
    double _yDeltaReal;

    bool registered = false;


private:

    double _lastAgentAbsoluteOrientation; // backup in case of collision

    int _iterations;

    void traceRayRGB(SDL_Surface *dst, int x1, int y1, int x2, int y2, Uint8 r, Uint8 g,
                     Uint8 b); // for screen rendering only
        int castSensorRay(SDL_Surface * image, double x1, double y1, double * x2pt, double * y2pt , int __maxValue = -1, int __idIgnore = -1 );
    
        void initRobotPhysics( );
        void applyRobotPhysics( );

	public:
		Robot( World *__world );
		virtual ~Robot();

		void reset() override;

		void stepBehavior() override;
		void stepBehavior(const Uint8* __keyboardStates) override;

		void callObserverPre(); // always called before stepBehavior.

        void callObserverPost(); // always called after stepBehavior.
    
		void applyDynamics(); // use transl/rot delta to compute x/y delta.

		//Moves the agent
		void move( int __recursiveIt = 0 ) override;
		
		void show(SDL_Surface *surface = gArena) override;

    bool isCollision();

    void setCoordReal(int __x, int __y); // agent is centered on point

    void registerRobot();

    void unregisterRobot();

    bool isRegistered() const;

    void behaviorUpdate_remoteController(const Uint8 *__keyStates);

    std::shared_ptr<Controller> getController()
    {
        return _controller;
    }

    std::shared_ptr<AgentObserver> getObserver()
    {
        return _agentObserver;
    }

    std::shared_ptr<WorldObserver> getWorldObserver();

    std::shared_ptr<RobotWorldModel> getWorldModel()
    {
        return _wm;
    }

    virtual std::string inspect(std::string prefix = "");

    void
    displayInfo(); // display input/output values on console. (used for inspect agent mode, cf. help on console) -- keep it simple: one line only.

    std::pair<int, int> findRandomLocation(int max_tries) const;

    // return a list of agents in the vincinity (ie. in the communication area)
    // the content of this list depends on the max communication range (see properties file).
    // works only if communication network is active.
		/* std::vector<int> getNeighbors(); */
};



#endif /* ROBOTAGENT_H */


