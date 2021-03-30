/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */

#include "Dummy/include/DummyController.h"
#include "World/World.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include <neuralnetworks/NeuralNetwork.h>

using namespace Neural;



DummyController::~DummyController()
{
}

void DummyController::reset()
{
}

void DummyController::step()
{

}

/*
void DummyController::step() // THIS IS A TEMPLATE FOR PRACTICAL APPLICATION (moving like an idiot , gathering sensory information for nothing)
{
    _iteration++;
    
    // *
    // * Parameter settings for the boid controller
    // *
    // *    Behaviors are ordered by priority, as follows:
    // *        if distance-to-wall < wallAvoidanceMinDist => triggers wall avoidance
    // *        if distance-to-center-of-mass < repulsiveRadius  => triggers repulsion
    // *        if distance-to-center-of-mass > attractionRadius => triggers attraction
    // *        if distance-to-center-of-mass in ]repulsiveRadius,attractionRadius[ => triggers orientation
    // *        if nobody around => move forward
    // *
    // *    All values are set in [0,1[
    // *
    
    double wallAvoidanceMinDist = gSensorRange*0.1;
    double repulsiveRadius = gSensorRange*0.1;
    double attractionRadius = gSensorRange*0.8;
    double orientationDelta = 0.0;
    
    
    // *
    // * get random information from surroundings!
    // *
    
    // Get distance to closest obstacle (wall or robot) from 8 sensors around the robot (works with the 12-sensors robot)
    double leftSensor = _wm->getCameraSensorValue(0,SENSOR_DISTANCEVALUE);
    double leftFwdSensor = _wm->getCameraSensorValue(2,SENSOR_DISTANCEVALUE);
    double fwdSensor = _wm->getCameraSensorValue(4,SENSOR_DISTANCEVALUE);
    double rightFwdSensor = _wm->getCameraSensorValue(6,SENSOR_DISTANCEVALUE);
    double rightSensor = _wm->getCameraSensorValue(8,SENSOR_DISTANCEVALUE);
    double rightBwdSensor = _wm->getCameraSensorValue(9,SENSOR_DISTANCEVALUE);
    double bwdSensor = _wm->getCameraSensorValue(10,SENSOR_DISTANCEVALUE);
    double leftBwdSensor = _wm->getCameraSensorValue(11,SENSOR_DISTANCEVALUE);

    int nbNeighbors = 0;
    
    for( int i = 0 ; i < _wm->_cameraSensorsNb ; i++)
    {
        int targetRawIndex = _wm->getObjectIdFromCameraSensor(i);
        
        if ( targetRawIndex >= gRobotIndexStartOffset )   // sensor ray bumped into a robot
        {
            int targetRobotIndex = targetRawIndex - gRobotIndexStartOffset; // convert image registering index into robot id.
            
            nbNeighbors++;
            
            double xMyself = _wm->_xReal;
            double yMyself = _wm->_yReal;
            double alphaMyself = _wm->_agentAbsoluteOrientation;
            
            double xNeighbor = gWorld->getRobot(targetRobotIndex)->getWorldModel()->_xReal;
            double yNeighbor = gWorld->getRobot(targetRobotIndex)->getWorldModel()->_yReal;
            double alphaNeighbor = gWorld->getRobot(targetRobotIndex)->getWorldModel()->_agentAbsoluteOrientation;

            double angleDeltaToNeighbor = getAngleToTarget(xMyself, yMyself, alphaMyself, xNeighbor, yNeighbor);

            std::cout << "robot no." << _wm->_id << " (x=" << xMyself << ",y=" << yMyself << "," << alphaMyself << "°) sees robot no." << targetRobotIndex << " (x=" << xNeighbor << ",y=" << yNeighbor << "," << alphaNeighbor << "°) at distance " << _wm->getCameraSensorValue(i,SENSOR_DISTANCEVALUE) << ", angle " << angleDeltaToNeighbor << "°!\n";
            // note: here, angle means at which angle does the robot sees its neighbor wrt to the direction it is facing.
            
            double delta_orientation = alphaMyself - alphaNeighbor;
            if ( delta_orientation >= 180.0 )
                delta_orientation = - ( 360.0 - delta_orientation );
            else
                if ( delta_orientation <= -180.0 )
                    delta_orientation = - ( - 360.0 - delta_orientation );
            delta_orientation = delta_orientation/180.0;
        }
        else
        {
            if ( targetRawIndex == 0 && _wm->getCameraSensorValue(i,SENSOR_DISTANCEVALUE) < 10 ) // closest wall
            {
                std::cout << "robot no." << _wm->_id << " sees a wall within distance=10 (distance: " << _wm->getCameraSensorValue(i,SENSOR_DISTANCEVALUE) << ")!\n";
            }
        }
    }

    // *
    // * move like an idiot!
    // *
    
    _wm->_desiredRotationalVelocity = 2 + (double)(randint()%10)/10.*0.02;
    _wm->_desiredTranslationalValue = 3;
    
}
*/
