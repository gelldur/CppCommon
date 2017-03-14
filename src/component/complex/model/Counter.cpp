/*
 * Counter.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: dawid
 */

#include "Counter.h"

namespace Dexode
{
namespace Component
{

void Counter::add(int count)
{
	_counter += count;
	if (_onChangeListener)
	{
		_onChangeListener(_counter);
	}
}

int Counter::get() const
{
	return _counter;
}

void Counter::set(int count)
{
	_counter = count;
	if (_onChangeListener)
	{
		_onChangeListener(_counter);
	}
}

void Counter::setOnChangeListener(const Listener& listener)
{
	_onChangeListener = listener;
}

void Counter::onAttach()
{
	inherited::onAttach();
}

void Counter::onDetach()
{
	inherited::onDetach();
}

}
} /* namespace Dexode */
