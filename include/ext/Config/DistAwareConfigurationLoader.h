/*
 * DistAwareConfigurationLoader.h
 */

#ifndef DISTAWARECONFIGURATIONLOADER_H
#define	DISTAWARECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class DistAwareConfigurationLoader : public ConfigurationLoader
{
public:
    DistAwareConfigurationLoader();

    ~DistAwareConfigurationLoader();

    std::shared_ptr<WorldObserver> make_WorldObserver(World *wm);

    std::shared_ptr<RobotWorldModel> make_RobotWorldModel();

    std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm);

    std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm);
};

#endif
