//
// Created by Dawid Drozd aka Gelldur on 07.06.17.
//
#pragma once

#include <functional>

#include <component/Base.h>

namespace Dexode
{
namespace Component
{

class Switchable : public Base
{
public:
	Switchable(std::function<void(bool isOn)> callback)
			: _callback(callback)
	{
	}

	bool is() const
	{
		return _isOn;
	}

	void set(bool isEnabled)
	{
		_isOn = isEnabled;
		_callback(_isOn);
	}

	bool flipOver()
	{
		set(!_isOn);
		return _isOn;
	}

private:
	std::function<void(bool isEnabled)> _callback;
	bool _isOn;
};

}
}
