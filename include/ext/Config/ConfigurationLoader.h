/*
 *	ConfigurationLoader.h
 */

#ifndef CONFIGURATIONLOADER_H
#define CONFIGURATIONLOADER_H

#include <core/World/PhysicalObject.h>
#include "RoboroboMain/common.h"

class WorldObserver;
class RobotWorldModel;
class AgentObserver;
class Controller;
class World;

class ConfigurationLoader
{
protected:
    ConfigurationLoader() = default;

public:
    virtual ~ConfigurationLoader() = default;

    static ConfigurationLoader *make_ConfigurationLoader(const std::string &configurationLoaderObjectName);

    virtual std::shared_ptr<WorldObserver> make_WorldObserver(World *wm) = 0;

    virtual std::shared_ptr<RobotWorldModel> make_RobotWorldModel() = 0;

    virtual std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm) = 0;

    virtual std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm) = 0;

    virtual std::shared_ptr<PhysicalObject> make_CustomObject(int id);
};


#endif
