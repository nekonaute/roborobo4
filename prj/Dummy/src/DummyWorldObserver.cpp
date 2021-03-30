/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "Dummy/include/DummyWorldObserver.h"
#include "Dummy/include/DummyController.h"
#include "World/World.h"
#include "Utilities/Graphics.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"

DummyWorldObserver::DummyWorldObserver( World* world ) : WorldObserver( world )
{
    _world = world;
}

DummyWorldObserver::~DummyWorldObserver()
{
    // nothing to do.
}

void DummyWorldObserver::reset()
{
    // nothing to do.
}

void DummyWorldObserver::stepPre()
{

}

void DummyWorldObserver::stepPost()
{
    // nothing to do.
}
