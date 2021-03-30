#if defined PRJ_DISTAWARE || !defined MODULAR

#include "Config/DistAwareConfigurationLoader.h"
#include "DistAware/include/DistAwareWorldObserver.h"
#include "DistAware/include/DistAwareAgentObserver.h"
#include "DistAware/include/DistAwareController.h"
#include "WorldModels/RobotWorldModel.h"


DistAwareConfigurationLoader::DistAwareConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

DistAwareConfigurationLoader::~DistAwareConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> DistAwareConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<DistAwareWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> DistAwareConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> DistAwareConfigurationLoader::make_AgentObserver(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<DistAwareAgentObserver>(wm);
}

std::shared_ptr<Controller> DistAwareConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<DistAwareController>(wm);
}


#endif
