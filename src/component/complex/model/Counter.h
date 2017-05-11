/*
 * Counter.h
 *
 *  Created on: Feb 21, 2015
 *      Author: dawid
 */

#pragma once

#include <functional>

#include <component/Base.h>

#include <predeclare.h>

namespace Dexode
{
namespace Component
{

class ComponentManager;

class Counter : public Base
{
	using inherited = Base;
public:
	using Listener = std::function<void(int)>;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void add(int count);
	void set(int count);
	int get() const;

	void setOnChangeListener(const Listener& listener);

private:
	int _counter = 0;
	Listener _onChangeListener;
};

}
} /* namespace Dexode */
