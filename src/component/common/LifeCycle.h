//
// Created by Dawid Drozd aka Gelldur on 13/11/16.
//

#pragma once

#include <component/Base.h>

namespace Dexode
{
namespace Component
{

class LifeCycle : public Base
{
	using inherited = Base;
public:
	LifeCycle();
	virtual ~LifeCycle();

	virtual void onAttach() override;
	virtual void onDetach() override;

protected:
	void onEnterNode();
	void onExitNode();

private:
	cocos2d::CCNode* _dummyNode = nullptr;
};

}
}
