//
// Created by Dawid Drozd aka Gelldur on 10/11/16.
//

#pragma once

#include <functional>
#include <memory>
#include <map>

#include <component/Base.h>
#include <EventCollector.h>

namespace Dexode
{
namespace Component
{

class UpdateComponent : public Base
{
	using inherited = Base;
public:
	UpdateComponent(std::function<void()> callback);

	virtual void onAttach() override;
	virtual void onDetach() override;

	template<typename ... Args>
	void updateOn(const std::shared_ptr<Notifier>& notifier, const Notification<Args...>& notification)
	{
		auto oldOne = std::move(_matrioshkaListen);//In future in cpp14 use move for lambda
		_matrioshkaListen = [this, oldOne, notifier, notification]()
		{
			if (oldOne)
			{
				oldOne();
			}

			getCollector(notifier).listen(notification, [this](Args...)
			{
				_onUpdateCallback();
			});
		};
	}

	void onEnter();
	void onExit();

private:
	std::function<void()> _onUpdateCallback;
	std::function<void()> _matrioshkaListen;
	EventCollector _onEnterCollector;
	std::map<Notifier*, EventCollector> _collectors;

	EventCollector& getCollector(const std::shared_ptr<Notifier>& notifier);
};

}
}
