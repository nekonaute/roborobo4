/*
 * TutorialConfigurationLoader.h
 */

#ifndef TUTORIALCONFIGURATIONLOADER_H
#define	TUTORIALCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TutorialConfigurationLoader : public ConfigurationLoader
{
public:
    TutorialConfigurationLoader();

    ~TutorialConfigurationLoader();

    std::shared_ptr<WorldObserver> make_WorldObserver(World *wm);

    std::shared_ptr<RobotWorldModel> make_RobotWorldModel();

    std::shared_ptr<AgentObserver> make_AgentObserver(std::shared_ptr<RobotWorldModel> wm);

    std::shared_ptr<Controller> make_Controller(std::shared_ptr<RobotWorldModel> wm);
};

#endif
