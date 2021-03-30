/*
 * TemplateMedeaConfigurationLoader.h
 */

#ifndef TEMPLATEMEDEACONFIGURATIONLOADER_H
#define TEMPLATEMEDEACONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TemplateMedeaConfigurationLoader : public ConfigurationLoader
{
private:

public:
    TemplateMedeaConfigurationLoader();

    ~TemplateMedeaConfigurationLoader();

    std::shared_ptr<WorldObserver> make_WorldObserver(World *wm);

    std::shared_ptr<RobotWorldModel> make_RobotWorldModel();

    std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm);

    std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm);
};



#endif
