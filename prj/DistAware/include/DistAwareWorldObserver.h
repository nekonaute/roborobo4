/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef DISTAWAREWORLDOBSERVER_H
#define DISTAWAREWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class DistAwareWorldObserver : public WorldObserver
{
	protected:
		
	public:
		DistAwareWorldObserver( World *__world );
		~DistAwareWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif

