/*
 * TemplateEEConfigurationLoader.h
 */

#ifndef TEMPLATEEECONFIGURATIONLOADER_H
#define TEMPLATEEECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TemplateEEConfigurationLoader : public ConfigurationLoader
{
private:

public:
    TemplateEEConfigurationLoader();

    ~TemplateEEConfigurationLoader();

    std::shared_ptr<WorldObserver> make_WorldObserver(World *wm);

    std::shared_ptr<RobotWorldModel> make_RobotWorldModel();

    std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm);

    std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm);
};



#endif
