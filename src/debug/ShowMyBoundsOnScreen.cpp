//
// Created by Dawid Drozd aka Gelldur on 02/11/16.
//

#include "ShowMyBoundsOnScreen.h"

#include <cocos2d.h>

namespace Dexode
{

void ShowMy::boundsOnScreen(cocos2d::CCNode* node)
{
	auto drawNode = cocos2d::DrawNode::create(1);
	node->addChild(drawNode, INT_MAX);
	if (node->getScaleX() != 0)
	{
		drawNode->setScaleX(1.0 / node->getScaleX());
	}
	if (node->getScaleY() != 0)
	{
		drawNode->setScaleY(1.0 / node->getScaleY());
	}

	drawNode->schedule([node, drawNode](float dt)
					   {
						   drawNode->clear();

						   auto rect = node->getBoundingBox();
						   drawNode->drawRect({0, 0}, {rect.size.width, rect.size.height}
											  , cocos2d::Color4F::MAGENTA);
					   }, 0, "boundsOnScreenUpdate");

	drawNode->setOnEnterCallback([node, drawNode]()
								 {
									 drawNode->clear();

									 auto rect = node->getBoundingBox();
									 drawNode->drawRect({0, 0}, {rect.size.width, rect.size.height}
														, cocos2d::Color4F::MAGENTA);
								 });
}

}
