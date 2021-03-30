/*
 * MedeaConfigurationLoader.h
 */

#ifndef DUMMYCONFIGURATIONLOADER_H
#define DUMMYCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"


class DummyConfigurationLoader : public ConfigurationLoader
{
private:

public:
    DummyConfigurationLoader();

    ~DummyConfigurationLoader();

    std::shared_ptr<WorldObserver> make_WorldObserver(World *wm);

    std::shared_ptr<RobotWorldModel> make_RobotWorldModel();

    std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm);

    std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm);
};



#endif