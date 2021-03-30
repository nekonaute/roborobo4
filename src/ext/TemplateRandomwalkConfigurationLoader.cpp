#if defined PRJ_TEMPLATERANDOMWALK || !defined MODULAR

#include "Config/TemplateRandomwalkConfigurationLoader.h"
#include "TemplateRandomwalk/include/TemplateRandomwalkWorldObserver.h"
#include "TemplateRandomwalk/include/TemplateRandomwalkAgentObserver.h"
#include "TemplateRandomwalk/include/TemplateRandomwalkController.h"
#include "WorldModels/RobotWorldModel.h"


TemplateRandomwalkConfigurationLoader::TemplateRandomwalkConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

TemplateRandomwalkConfigurationLoader::~TemplateRandomwalkConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> TemplateRandomwalkConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<TemplateRandomwalkWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> TemplateRandomwalkConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> TemplateRandomwalkConfigurationLoader::make_AgentObserver(
        std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateRandomwalkAgentObserver>(wm);
}

std::shared_ptr<Controller> TemplateRandomwalkConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateRandomwalkController>(wm);
}


#endif
