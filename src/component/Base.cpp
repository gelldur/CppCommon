//
// Created by Dawid Drozd aka Gelldur on 10/11/16.
//

#include "Base.h"

#include <component/ComponentManager.h>

namespace Dexode
{
namespace Component
{

void Base::onAttach()
{
	assert(_owner);//_owner should be set before onAttach() !
}

cocos2d::Node* Base::getWorkingNode()
{
	return getOwner()->getWorkingNode();
}

}
}
