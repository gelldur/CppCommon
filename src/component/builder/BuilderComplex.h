/*
 * BuilderComplex.h
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#pragma once

#include "Builder.h"

namespace Dexode
{
namespace Component
{

class ComponentManager;

class BuilderComplex
{
public:

	BuilderComplex(cocos2d::CCNode* node)
			: _builder(Builder::create(node))
	{
	}

	~BuilderComplex()
	{
	}

	static BuilderComplex create(cocos2d::CCNode* node)
	{
		return {node};
	}

	//TODO make optional arguments?
	BuilderComplex& addBehaviourButton(const Builder::OnClick& onClick)
	{
		_builder.addTouchable().setClickable(onClick);
		return *this;
	}

	BuilderComplex& addBehaviourDraggable()
	{
		_builder.addTouchable().setDraggable();
		return *this;
	}

	ComponentManager* getComponentManager() const;

	ComponentManager* operator->() const;

private:
	Builder _builder;
};

} /* namespace Component */
} /* namespace Dexode */
