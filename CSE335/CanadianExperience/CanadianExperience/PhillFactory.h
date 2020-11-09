/**
 * \file PhillFactory.h
 *
 * \author Spencer D Cassetta
 *
 *
 */

#include "ActorFactory.h"
#pragma once
/**
 * Factory class that builds the Phill character
 */
class CPhillFactory
{
public:
	/**creates Phill
	*\return the phill actor it has created*/
	std::shared_ptr<CActor> Create();
};

