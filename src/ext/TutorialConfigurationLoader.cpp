#if defined PRJ_TUTORIAL || !defined MODULAR

#include "Config/TutorialConfigurationLoader.h"
#include "Tutorial/include/TutorialWorldObserver.h"
#include "Tutorial/include/TutorialAgentObserver.h"
#include "Tutorial/include/TutorialController.h"
#include "WorldModels/RobotWorldModel.h"


TutorialConfigurationLoader::TutorialConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

TutorialConfigurationLoader::~TutorialConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> TutorialConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<TutorialWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> TutorialConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> TutorialConfigurationLoader::make_AgentObserver(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TutorialAgentObserver>(wm);
}

std::shared_ptr<Controller> TutorialConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TutorialController>(wm);
}


#endif
