#if defined PRJ_TEMPLATEMEDEA || !defined MODULAR

#include "Config/TemplateMedeaConfigurationLoader.h"
#include "TemplateMedea/include/TemplateMedeaWorldObserver.h"
#include "TemplateMedea/include/TemplateMedeaAgentObserver.h"
#include "TemplateMedea/include/TemplateMedeaController.h"
#include "WorldModels/RobotWorldModel.h"

TemplateMedeaConfigurationLoader::TemplateMedeaConfigurationLoader()
{
}

TemplateMedeaConfigurationLoader::~TemplateMedeaConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> TemplateMedeaConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<TemplateMedeaWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> TemplateMedeaConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> TemplateMedeaConfigurationLoader::make_AgentObserver(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateMedeaAgentObserver>(wm);
}

std::shared_ptr<Controller> TemplateMedeaConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateMedeaController>(wm);
}

#endif
