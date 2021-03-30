#if defined PRJ_TEMPLATEVANILLAEE || !defined MODULAR

#include "Config/TemplateVanillaEEConfigurationLoader.h"
#include "TemplateVanillaEE/include/TemplateVanillaEEWorldObserver.h"
#include "TemplateVanillaEE/include/TemplateVanillaEEAgentObserver.h"
#include "TemplateVanillaEE/include/TemplateVanillaEEController.h"
#include "WorldModels/RobotWorldModel.h"

TemplateVanillaEEConfigurationLoader::TemplateVanillaEEConfigurationLoader()
{
}

TemplateVanillaEEConfigurationLoader::~TemplateVanillaEEConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> TemplateVanillaEEConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<TemplateVanillaEEWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> TemplateVanillaEEConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> TemplateVanillaEEConfigurationLoader::make_AgentObserver(
        std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateVanillaEEAgentObserver>(wm);
}

std::shared_ptr<Controller> TemplateVanillaEEConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateVanillaEEController>(wm);
}

#endif
