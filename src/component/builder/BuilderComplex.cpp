/*
 * BuilderComplex.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: dawid
 */
#include "BuilderComplex.h"

#include <component/ComponentManager.h>

namespace Dexode
{
namespace Component
{

ComponentManager* BuilderComplex::getComponentManager() const
{
	return _builder.getComponentManager();
}

ComponentManager* BuilderComplex::operator->() const
{
	return _builder.operator->();
}

}
}
