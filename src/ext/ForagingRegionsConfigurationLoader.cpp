#if defined PRJ_FORAGINGREGIONS || !defined MODULAR

#include "Config/ForagingRegionsConfigurationLoader.h"
#include "ForagingRegions/include/ForagingRegionsWorldObserver.h"
#include "ForagingRegions/include/ForagingRegionsAgentObserver.h"
#include "ForagingRegions/include/ForagingRegionsController.h"
#include "WorldModels/RobotWorldModel.h"

ForagingRegionsConfigurationLoader::ForagingRegionsConfigurationLoader()
{
}

ForagingRegionsConfigurationLoader::~ForagingRegionsConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> ForagingRegionsConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<ForagingRegionsWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> ForagingRegionsConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> ForagingRegionsConfigurationLoader::make_AgentObserver(
        std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<ForagingRegionsAgentObserver>(wm);
}

std::shared_ptr<Controller> ForagingRegionsConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<ForagingRegionsController>(wm);
}

#endif
