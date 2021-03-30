/*
 *  World.h
 *  roborobo
 *
 *  Created by Nicolas on 16/01/09.
 *
 */


#ifndef WORLD_H
#define WORLD_H

#include "RoboroboMain/common.h"

class WorldObserver;
class Robot;
class LandmarkObject;

class World
{
protected:

    int _iterations;

    //True if there is a variation in the number of agent
    bool _agentsVariation;

    std::shared_ptr<WorldObserver> _worldObserver;

public:

    World();

    ~World();

    bool loadFiles();
    //bool loadProperties( std::string __propertiesFilename );

    void initWorld(std::function<void()> callbackOnceObjectsAreCreated = [](){});

    void updateWorld(const Uint8 *__keyboardStates = NULL);

    std::shared_ptr<Robot> getRobot(int index);

    bool isRobotRegistered(int index);

    //delete an agent from the simulator. No other functions to call
    // THIS FUNCTION SHOULD NOT BE IMPLEMENTED AND SHOULD NEVER BE CALLED
    // Roborobo assumes that the 'agents' list indexes matches agent's id.
    void deleteRobot(int index);

    //add an agent in the simulator. No other functions to call
    void addRobot(std::shared_ptr<Robot> robot);

    void deleteLandmark(int __index);

    void addLandmark(std::shared_ptr<LandmarkObject> objectToAdd);

    int getIterations();

    std::shared_ptr<WorldObserver> getWorldObserver();

    int getNbOfRobots();
};



#endif // WORLD_H

