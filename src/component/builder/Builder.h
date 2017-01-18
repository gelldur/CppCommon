/*
 * Builder.h
 *
 *  Created on: Jan 21, 2015
 *      Author: dawid
 */

#pragma once

#include "Flags.h"

#include <functional>
#include <stdexcept>

namespace cocos2d
{
class Node;

class Touch;
}

namespace Dexode
{
namespace Component
{

class OnDragEvent;

class ComponentManager;

class Builder
{
public:
	using OnClick = std::function<void(cocos2d::Touch*)>;
	using OnTouch = std::function<void(OnDragEvent)>;

	static Builder create(cocos2d::Node* node)
	{
		return {node};
	}

	Builder(cocos2d::Node* node);

	/**
	 * @param node node which should be a child of node used for create.
	 *  This node will be added to touchable area of our parent node.
	 *   Default value means that we want ourselves to touchable list
	 * @return
	 */
	Builder& addTouchable(cocos2d::Node* node = nullptr);

	Builder& setDraggable(int flags = Config::Draggable::EMPTY);

	Builder& setDraggable(const OnTouch& onTouchBegan, const OnTouch& onTouchMoved, const OnTouch& onTouchEnded);

	Builder& setDraggableOnTouchBegan(const OnTouch& onTouchBegan);

	Builder& setDraggableOnTouchMoved(const OnTouch& onTouchMoved);

	Builder& setDraggableOnTouchEnded(const OnTouch& onTouchEnded);

	Builder& setClickable(const OnClick& onClick);

	ComponentManager* getComponentManager() const;

	ComponentManager* operator->() const
	{
		if (_manager == nullptr)
		{
			throw std::runtime_error("null pointer exception");
		}
		return _manager;
	}

private:
	cocos2d::Node* _node = nullptr;
	ComponentManager* _manager = nullptr;
};

} /* namespace Component */
} /* namespace Dexode */
