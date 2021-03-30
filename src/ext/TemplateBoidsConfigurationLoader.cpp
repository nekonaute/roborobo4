#if defined PRJ_TEMPLATEBOIDS || !defined MODULAR

#include "Config/TemplateBoidsConfigurationLoader.h"
#include "TemplateBoids/include/TemplateBoidsWorldObserver.h"
#include "TemplateBoids/include/TemplateBoidsAgentObserver.h"
#include "TemplateBoids/include/TemplateBoidsController.h"
#include "WorldModels/RobotWorldModel.h"

TemplateBoidsConfigurationLoader::TemplateBoidsConfigurationLoader()
{
}

TemplateBoidsConfigurationLoader::~TemplateBoidsConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> TemplateBoidsConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<TemplateBoidsWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> TemplateBoidsConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> TemplateBoidsConfigurationLoader::make_AgentObserver(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateBoidsAgentObserver>(wm);
}

std::shared_ptr<Controller> TemplateBoidsConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateBoidsController>(wm);
}

#endif
