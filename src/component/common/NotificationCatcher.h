/*
 * NotificationCatcher.h
 *
 *  Created on: Jan 26, 2015
 *      Author: dawid
 */

#pragma once

#include <functional>

#include <Notifier.h>
#include <EventCollector.h>
#include <component/Base.h>

namespace Dexode
{
namespace Component
{

class NotificationCatcher : public Base
{
	using inherited = Base;
public:
	NotificationCatcher(Notifier& notifier);

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onEnter()
	{
		_onEnter();
	}

	void onExit()
	{
		_onExit();
	}

	template<typename ... Args>
	void setListener(const Notification<Args...>& notification
			, const std::function<void(Args...)>& callback)
	{
		if (_onEnter)
		{
			assert(false && "Already set");
			return;
		}

		_onEnter = [this, notification, callback]()
		{
			_collectorAdded.listen(notification, callback);
		};
		_onExit = [this]()
		{
			_collectorAdded.unlistenAll();
		};
	}

private:
	std::function<void()> _onEnter;
	std::function<void()> _onExit;

	EventCollector _collector;
	EventCollector _collectorAdded;
};

} /* namespace Component */
} /* namespace Dexode */
