//
// Created by Dawid Drozd aka Gelldur on 26/10/16.
//

#pragma once

#include <memory>
#include <type_traits>
#include <stdexcept>

#include <Ref.h>

namespace Dexode
{

/**
 * RAII
 */

template<class T>
class RefHolder
{
	static_assert(std::is_base_of<cocos2d::Ref, T>::value, "T must inherit from cocos2d::Ref");
public:
	RefHolder(T* ref = nullptr)
			: _ref(ref)
	{
		retain();
	}

	~RefHolder()
	{
		release();
	}

	RefHolder(RefHolder const& other)
			: RefHolder(other._ref)
	{
	}

	RefHolder(RefHolder&& other)
			: _ref(other.reset())
	{
	}

	RefHolder& operator=(T* other)
	{
		if (_ref == other)
		{
			return *this;
		}

		auto previous = _ref;

		_ref = other;
		retain();

		if (previous != nullptr)
		{
			previous->release();
		}

		return *this;
	}

	RefHolder& operator=(RefHolder const& other)
	{
		if (this == &other)
		{
			return *this;
		}

		auto previous = _ref;

		_ref = other._ref;
		retain();

		if (previous != nullptr)
		{
			previous->release();
		}

		return *this;
	}

	RefHolder& operator=(RefHolder&& other)
	{
		if (this == &other)
		{
			return *this;
		}

		auto previous = _ref;
		_ref = other.reset();

		if (previous != nullptr)
		{
			previous->release();
		}

		return *this;
	}

	T* reset()
	{
		auto ref = _ref;
		_ref = nullptr;
		return ref;
	}

	void release()
	{
		if (_ref != nullptr)
		{
			_ref->release();
		}
		_ref = nullptr;
	}

	T* autorelease()
	{
		if (_ref != nullptr)
		{
			_ref->autorelease();
		}
		auto ref = _ref;
		_ref = nullptr;
		return ref;
	}

	operator bool() const
	{
		return _ref != nullptr;
	}

	bool isNull() const
	{
		return _ref == nullptr;
	}

	bool operator!=(T* other) const
	{
		return _ref != other;
	}

	bool operator==(T* other) const
	{
		return _ref == other;
	}

	T* operator->() const
	{
		if (_ref == nullptr)
		{
			throw std::runtime_error("null pointer exception");
		}
		return _ref;
	}

	T* get() const
	{
		return _ref;
	}

private:
	T* _ref = nullptr;

	void retain()
	{
		if (_ref != nullptr)
		{
			_ref->retain();
		}
	}
};

}
