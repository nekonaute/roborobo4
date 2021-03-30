#if defined PRJ_TEMPLATEWANDER || !defined MODULAR

#include "Config/TemplateWanderConfigurationLoader.h"
#include "TemplateWander/include/TemplateWanderWorldObserver.h"
#include "TemplateWander/include/TemplateWanderAgentObserver.h"
#include "TemplateWander/include/TemplateWanderController.h"
#include "WorldModels/RobotWorldModel.h"


TemplateWanderConfigurationLoader::TemplateWanderConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

TemplateWanderConfigurationLoader::~TemplateWanderConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> TemplateWanderConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<TemplateWanderWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> TemplateWanderConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver>
TemplateWanderConfigurationLoader::make_AgentObserver(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateWanderAgentObserver>(wm);
}

std::shared_ptr<Controller> TemplateWanderConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<TemplateWanderController>(wm);
}


#endif
