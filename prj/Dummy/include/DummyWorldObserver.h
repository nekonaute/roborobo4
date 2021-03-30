/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef DUMMYWORLDOBSERVER_H
#define DUMMYWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class DummyWorldObserver : public WorldObserver
{
public:
    DummyWorldObserver(World *world);
    ~DummyWorldObserver();
    
    void reset();
    void stepPre();
    void stepPost();

};

#endif
