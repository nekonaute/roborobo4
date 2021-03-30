/*
 * TemplateWanderConfigurationLoader.h
 */

#ifndef TEMPLATEWANDERCONFIGURATIONLOADER_H
#define	TEMPLATEWANDERCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TemplateWanderConfigurationLoader : public ConfigurationLoader
{
public:
    TemplateWanderConfigurationLoader();

    ~TemplateWanderConfigurationLoader();

    std::shared_ptr<WorldObserver> make_WorldObserver(World *wm);

    std::shared_ptr<RobotWorldModel> make_RobotWorldModel();

    std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm);

    std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm);
};

#endif
