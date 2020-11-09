#pragma once
#include <memory>
#include <iostream>
#include "Picture.h"
/**
 * A factory class that builds our picture.
 */
class CPictureFactory
{
public:
	/**creates a picture
	*\return picture it has created*/
	std::shared_ptr<CPicture> Create();
};

