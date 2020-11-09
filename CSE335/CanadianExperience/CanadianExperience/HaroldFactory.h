#include "ActorFactory.h"
#pragma once
/**
 * Factory class that builds the Harold character
 */
class CHaroldFactory
{
public:
	/**creates Harold
	*\return the harold actor it has created*/
	std::shared_ptr<CActor> Create();
};

