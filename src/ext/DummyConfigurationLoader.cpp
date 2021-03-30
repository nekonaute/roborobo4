#if defined PRJ_DUMMY || !defined MODULAR

#include "Config/DummyConfigurationLoader.h"
#include "Dummy/include/DummyWorldObserver.h"
#include "Dummy/include/DummyAgentObserver.h"
#include "Dummy/include/DummyController.h"
#include "WorldModels/RobotWorldModel.h"

DummyConfigurationLoader::DummyConfigurationLoader()
{
}

DummyConfigurationLoader::~DummyConfigurationLoader()
{
	//nothing to do
}

std::shared_ptr<WorldObserver> DummyConfigurationLoader::make_WorldObserver(World *wm)
{
    return std::make_shared<DummyWorldObserver>(wm);
}

std::shared_ptr<RobotWorldModel> DummyConfigurationLoader::make_RobotWorldModel()
{
    return std::make_shared<RobotWorldModel>();
}

std::shared_ptr<AgentObserver> DummyConfigurationLoader::make_AgentObserver(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<DummyAgentObserver>(wm);
}

std::shared_ptr<Controller> DummyConfigurationLoader::make_Controller(std::shared_ptr<RobotWorldModel> wm)
{
    return std::make_shared<DummyController>(wm);
}

#endif
