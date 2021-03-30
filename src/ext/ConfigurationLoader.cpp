#include <ext/Config/DummyConfigurationLoader.h>
#include "Config/ConfigurationLoader.h"
#include "Config/TemplateWanderConfigurationLoader.h"
#include "Config/TemplateBoidsConfigurationLoader.h"
#include "Config/TemplateRandomwalkConfigurationLoader.h"
#include "Config/TemplateEEConfigurationLoader.h"
#include "Config/TemplateVanillaEEConfigurationLoader.h"
#include "Config/TemplateMedeaConfigurationLoader.h"
#include "Config/ForagingRegionsConfigurationLoader.h"
#include "Config/TutorialConfigurationLoader.h"
#include "Config/DistAwareConfigurationLoader.h"
//###DO-NOT-DELETE-THIS-LINE###TAG:INCLUDE###//



ConfigurationLoader *ConfigurationLoader::make_ConfigurationLoader(const std::string &configurationLoaderObjectName)
{
    if (false)
    {
        // >>> Never reached
    }
#if defined PRJ_TEMPLATEWANDER || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateWanderConfigurationLoader")
    {
        return new TemplateWanderConfigurationLoader();
    }
#endif
#if defined PRJ_TEMPLATEBOIDS || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateBoidsConfigurationLoader")
    {
        return new TemplateBoidsConfigurationLoader();
    }
#endif
#if defined PRJ_TEMPLATERANDOMWALK || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateRandomwalkConfigurationLoader")
    {
        return new TemplateRandomwalkConfigurationLoader();
    }
#endif
#if defined PRJ_TEMPLATEEE || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateEEConfigurationLoader")
    {
        return new TemplateEEConfigurationLoader();
    }
#endif
#if defined PRJ_TEMPLATEVANILLAEE || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateVanillaEEConfigurationLoader")
    {
        return new TemplateVanillaEEConfigurationLoader();
    }
#endif
#if defined PRJ_TEMPLATEMEDEA || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateMedeaConfigurationLoader")
    {
        return new TemplateMedeaConfigurationLoader();
    }
#endif
#if defined PRJ_FORAGINGREGIONS || !defined MODULAR
    else if (configurationLoaderObjectName == "ForagingRegionsConfigurationLoader")
    {
        return new ForagingRegionsConfigurationLoader();
    }
#endif
#if defined PRJ_TUTORIAL || !defined MODULAR
    else if (configurationLoaderObjectName == "TutorialConfigurationLoader")
    {
        return new TutorialConfigurationLoader();
    }
#endif
    else if (configurationLoaderObjectName == "DummyConfigurationLoader")
    {
        return new DummyConfigurationLoader();
    }
#if defined PRJ_DISTAWARE || !defined MODULAR
	else if (configurationLoaderObjectName == "DistAwareConfigurationLoader" )
	{
		return new DistAwareConfigurationLoader();
	}
#endif
        //###DO-NOT-DELETE-THIS-LINE###TAG:SWITCH###//
    else
    {
        return nullptr;
    }

}

std::shared_ptr<PhysicalObject> ConfigurationLoader::make_CustomObject(int id)
{
    throw std::runtime_error("No custom object definition for this Configuration");
    return nullptr;
}
