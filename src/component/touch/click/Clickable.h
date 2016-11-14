/*
 * Clickable.h
 *
 *  Created on: Jan 21, 2015
 *      Author: dawid
 */

#pragma once

#include <functional>

#include <component/Base.h>
#include <EventCollector.h>

namespace cocos2d
{
class Touch;
}

namespace Dexode
{
namespace Component
{

class Clickable : public Base
{
	using inherited = Base;
public:
	using OnClick = std::function<void(cocos2d::Touch*)>;

	Clickable(const OnClick& onClick);

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onTouchEnded(cocos2d::Touch* touch);

private:
	const OnClick _onClick;
	EventCollector _collector;
};

} /* namespace Component */
} /* namespace Dexode */
