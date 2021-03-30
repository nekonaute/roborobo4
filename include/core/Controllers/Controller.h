/*
 *  Controller.h
 *  roborobo-online
 *
 *  Created by Nicolas on 19/03/09.
 *  Copyright 2009. All rights reserved.
 *
 */


#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <iostream>
#include <World/PhysicalObject.h>
#include <Agents/Robot.h>
#include "RoboroboMain/common.h"
#include "Utilities/Geometry.h"

#ifdef PYROBOROBO
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
#endif

class RobotWorldModel;

class Controller
{
private:

    int lastRefreshIteration;

    bool checkRefresh() const;

    void refreshInputs();

protected:

    std::shared_ptr<RobotWorldModel> _wm;
    std::vector<double> distanceSensors;
    std::vector<double> angleSensors;
    std::vector<int> objectDetectors;
    std::vector<int> objectTypeDetectors;
    std::vector<int> robotDetectors;
    std::vector<int> robotGroupDetector;
    std::vector<double> robotRelativeOrientationDetectors;
    std::vector<int> wallDetectors;
    std::vector<std::shared_ptr<PhysicalObject>> objectInstanceDetectors;
    std::vector<std::shared_ptr<Controller>> robotControllerDetectors;
    std::vector<std::shared_ptr<Robot>> robotInstanceDetectors;

#ifdef PYROBOROBO
    std::vector<py::handle> pyObjectInstanceDetectors;
    std::vector<py::handle> pyRobotControllerDetectors;
#endif



    double redGroundDetectors;
    double greenGroundDetectors;
    double blueGroundDetectors;

    double landmark_closest_DistanceDetector;
    double landmark_closest_DirectionDetector;

    // remark: other landmarks can be accessed directly from _wm->updateLandmarkSensor(id_landmark).

public:

    Controller();

    Controller(std::shared_ptr<RobotWorldModel> __wm);

    virtual ~Controller();

    virtual void reset() = 0;

    virtual void step() = 0;

    std::shared_ptr<RobotWorldModel> getWorldModel()
    {
        return _wm;
    }

    virtual std::string inspect(std::string prefix = "");

    // #### #### #### #### #### #### #### #### #### #### #### #### ####
        //
        // Accessing methods
        //
        // The following methods can be used to access all information
        // available to the robot. These are wrappers for more complex
        // internal functions and should be used to write your projects.
        //
        // #### #### #### #### #### #### #### #### #### #### #### #### ####

        // returns normalized distance in [0,1]
        double getDistanceAt( int sensorId )
        {
            if ( checkRefresh() == false ) { refreshInputs(); }
            return distanceSensors[sensorId];
        }

        double getSensorAngleAt(int sensorId);

        std::vector<double>& getAllSensorAngles();

        std::vector<double>& getAllDistances()
        {
            if ( checkRefresh() == false ) { refreshInputs(); }
            return distanceSensors;
        }

        // returns 0 (no object) or 1 (object)
        int getObjectAt( int sensorId );

        // returns target object's type (relevant if target object exists)
        // returns an integer. Check PhysicalObjectFactory class for existing types.
        // most common types are: 0 (round), 1 (energy item), 2 (gate), 3 (switch), 4 (movable), ...?
        int getObjectTypeAt( int sensorId );
    
        // returns robot's id, or -1 (not a robot)
        int getRobotIdAt( int sensorId );
    
        // returns target robot's group, or -1
        int getRobotGroupIdAt( int sensorId );

        // returns 0 (not a wall) or 1 (wall)
        int getWallAt( int sensorId );
    
        // returns target robot's orientation wrt this robot's facing direction (relevant if target robot exists), mapped to [-1,+1]
        // i.e. if both robots roughly go in the same direction, it returns a value around 0. If opposite directions, value returned is close to -1 or +1  
        double getRobotRelativeOrientationAt( int sensorId );

    // return the target robot's controller
    // enable to access *all* information from the target robot's controller
    // this is a very powerful method and should be used with care
    // don't forget to cast the result to the relevant Controller subclass
    // example of use: implement message-based communication (if Controller class is extended)
    std::shared_ptr<Controller> getRobotControllerAt(int sensorId);
    
        // return a value in [0,1] (red component)
        double getRedGroundDetector( );
    
        // return a value in [0,1] (green component)
        double getGreenGroundDetector( );

        // return a value in [0,1] (blue component)
        double getBlueGroundDetector( );
    
        // return distance to closest landmark (pixel-based euclidian distance - normalized in [0,1] -- using maximum possible distance in arena
        double getClosestLandmarkDistance()
        {
            if ( checkRefresh() == false ) { refreshInputs(); }
            return landmark_closest_DistanceDetector;
        }

        // return angle to closest landmark - mapped to [-1,+1]
        double getClosestLandmarkOrientation()
        {
            if ( checkRefresh() == false ) { refreshInputs(); }
            return landmark_closest_DirectionDetector;
        }
    
        // get actual absolute orientation (wrt. east / rightwards -- Clock-wise) -- mapped to [-1,+1]
        double getOrientation();
    
        // get actual linear speed
        double getLinearSpeed();
    
        // get x/y coordinate in the arena
        Point2d getPosition();

        // setTranslation(value) takes a value in [-1,+1]
        void setTranslation( double value );
    
        // setRotation(value) takes a value in [-1,+1]
        void setRotation( double value );
    
        // get this robot Id (anything from 0 to gInitialNumberOfRobots)
        int getId();
    
        // get this robot "true" actual translational speed (ie. actual measured translation per timestep, not desired -- the two may differ)
        double getActualTranslation();
    
        // get this robot "true" actual rotational speed (ie. actual measured rotation per timestep, not desired -- the two may differ)
        double getActualRotation();
    
        // robot's orientation w.r.t. North (ie. upwards), mapped in [-1,+1]
        double getCompass();
    
        // #### #### #### #### #### #### #### #### #### #### #### #### ####

    std::shared_ptr<PhysicalObject> getObjectInstanceAt(int sensorId);
    std::shared_ptr<Robot> getRobotInstanceAt(int sensorId);


    std::vector<int> &getAllRobotIds();

    std::vector<int> &getAllWalls();

    std::vector<double> &getAllRobotRelativeOrientations();

    std::vector<int> &getAllRobotGroupIds();

    std::vector<int> &getAllObjectTypes();

    std::vector<std::shared_ptr<PhysicalObject>>& getAllObjectInstances();
    std::vector<int>& getAllObjects();

    std::vector<std::shared_ptr<Controller>>& getAllRobotControllers();

    std::vector<std::shared_ptr<Robot>>& getAllRobotInstances();

#ifdef PYROBOROBO
    std::vector<py::handle> & getAllPyObjectInstances();
    std::vector<py::handle> & getAllPyRobotControllers();
    py::handle getPyRobotControllerAt(int sensorId);
    py::handle getPyObjectInstanceAt(int sensorId);


#endif

};


#endif
