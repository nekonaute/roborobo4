#if defined PRJ_TEMPLATEEE || !defined MODULAR

#include "Config/TemplateEEConfigurationLoader.h"

#include "TemplateEE/include/TemplateEEWorldObserver.h"
#include "TemplateEE/include/TemplateEEAgentObserver.h"
#include "TemplateEE/include/TemplateEEController.h"

#include "WorldModels/RobotWorldModel.h"

TemplateEEConfigurationLoader::TemplateEEConfigurationLoader()
{
}

TemplateEEConfigurationLoader::~TemplateEEConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> TemplateEEConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<TemplateEEWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> TemplateEEConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> TemplateEEConfigurationLoader::make_AgentObserver(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateEEAgentObserver>(wm);
}

std::shared_ptr<Controller> TemplateEEConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateEEController>(wm);
}

#endif
