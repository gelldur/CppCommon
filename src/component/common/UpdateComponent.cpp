//
// Created by Dawid Drozd aka Gelldur on 10/11/16.
//

#include "UpdateComponent.h"

#include <component/common/LifeCycleEvents.h>

namespace Dexode
{
namespace Component
{

UpdateComponent::UpdateComponent(std::function<void()> callback)
		: _onUpdateCallback(std::move(callback))
{
}

void UpdateComponent::onAttach()
{
	inherited::onAttach();
	_onEnterCollector = listenForOnEnterOnExit(this);
}

void UpdateComponent::onDetach()
{
	_onEnterCollector.unlistenAll();
	_collectors.clear();
	inherited::onDetach();
}

EventCollector& UpdateComponent::getCollector(const std::shared_ptr<Notifier>& notifier)
{
	auto found = _collectors.find(notifier.get());
	if (found == _collectors.end())
	{
		_collectors.emplace(notifier.get(), EventCollector{notifier});
	}

	return _collectors[notifier.get()];
}

void UpdateComponent::onEnter()
{
	_onUpdateCallback();
	_matrioshkaListen();
}

void UpdateComponent::onExit()
{
	_collectors.clear();
}

}
}
