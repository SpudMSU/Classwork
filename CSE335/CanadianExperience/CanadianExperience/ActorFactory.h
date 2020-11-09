/**
 * \file ActorFactory.h
 *
 * \author Spencer D Cassetta
 *
 *
 */
#pragma once
#include "Actor.h"
/**
 * Abstract base class for actor factories.
 */
class CActorFactory
{
	/**creates an actor
	*\return actor it has created*/
	virtual std::shared_ptr<CActor> Create();
};

