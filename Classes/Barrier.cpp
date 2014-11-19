//
//  Barrier.cpp
//  Tank
//
//  Created by wwj on 14/11/19.
//
//

#include "Barrier.h"

Barrier* Barrier::create(const char *pic, int index, int blood)
{
    Barrier* barrier = new Barrier();
    if (!barrier->initWithFile(pic)) {
        CC_SAFE_DELETE(barrier);
        return NULL;
    }
    
    barrier->index = index;
    barrier->blood = blood;
    return barrier;
}


bool Barrier::isCollision(cocos2d::Sprite *target)
{
    Vec2 targetPos = target->getPosition();
    Size targetSize = target->getContentSize();
    float twidth = targetSize.width+getContentSize().width;
    float theight = targetSize.height+getContentSize().height;
    
    return (abs(targetPos.x-getPosition().x) < twidth/2) || (abs(targetPos.y-getPosition().y) < theight/2);
}