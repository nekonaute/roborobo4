/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef DISTAWARECONTROLLER_H
#define DISTAWARECONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class DistAwareController : public Controller
{
public:
    DistAwareController(std::shared_ptr<RobotWorldModel> _wm);

    ~DistAwareController();

    void reset();

    void step();

    float distanceToRobot(int id);

};


#endif

