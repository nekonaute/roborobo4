/*
 * TemplateVanillaEEConfigurationLoader.h
 */

#ifndef TEMPLATEVANILLAEECONFIGURATIONLOADER_H
#define TEMPLATEVANILLAEECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TemplateVanillaEEConfigurationLoader : public ConfigurationLoader
{
private:

public:
    TemplateVanillaEEConfigurationLoader();

    ~TemplateVanillaEEConfigurationLoader();

    std::shared_ptr<WorldObserver> make_WorldObserver(World *wm);

    std::shared_ptr<RobotWorldModel> make_RobotWorldModel();

    std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm);

    std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm);
};



#endif
