/*
 * NotificationCatcher.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: dawid
 */

#include "NotificationCatcher.h"

#include <component/common/LifeCycleEvents.h>

namespace Dexode
{
namespace Component
{

NotificationCatcher::NotificationCatcher(Notifier& notifier)
		: _collectorAdded(notifier)
{
}

void NotificationCatcher::onAttach()
{
	inherited::onAttach();
	_collector = listenForOnEnterOnExit(this);
}

void NotificationCatcher::onDetach()
{
	_collector.unlistenAll();
	inherited::onDetach();
}

} /* namespace Component */
} /* namespace Dexode */
