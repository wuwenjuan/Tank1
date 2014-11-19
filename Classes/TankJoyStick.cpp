//
//  TankJoyStick.cpp
//  Tank
//
//  Created by wwj on 14/11/4.
//
//

#include "TankJoyStick.h"
#include "GameDefine.h"

bool TankJoyStick::init()
{
    if(!Sprite::init())
        return false;
    
    setContentSize(Size(220,220));
    centerPos = Vec2(getContentSize().width/2,getContentSize().height/2);
    auto bg = Sprite::create("direction.png");
    bg->setPosition(centerPos);
    addChild(bg);
    
    radius = getContentSize().width/2;
    radiusSqr = radius*radius;
    
    thumb = Sprite::create("center.png");
    thumb->cocos2d::Node::setPosition(centerPos);
    addChild(thumb);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TankJoyStick::onTouchBegin, this);
    listener->onTouchMoved = CC_CALLBACK_2(TankJoyStick::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(TankJoyStick::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    schedule(schedule_selector(TankJoyStick::update));
    return true;
}

void TankJoyStick::updateVelocity(Vec2 point)
{
    float dsq = point.x*point.x+point.y*point.y;
    float angle = atan2f(point.y, point.x);
    if (angle<0) {
        angle += 2*pi;
    }
    float dx = point.x;
    float dy = point.y;
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    
    if (dsq>radiusSqr) {
        dx = cosAngle*radius;
        dy = sinAngle*radius;
    }
    
    velocity = Point(dx/radius,dy/radius);
    stickMovePos = Vec2(dx,dy);
}

bool TankJoyStick::onTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto orilocation = Director::getInstance()->convertToGL(touch->getLocationInView());
    auto location = convertToNodeSpaceAR(orilocation);
    
    if (location.x < -radius || location.x > radius || location.y<-radius || location.y>radius) {
        return  false;
    }
    else
    {
        float dsq = location.x*location.x+location.y*location.y;
        if (dsq<radiusSqr) {
            updateVelocity(location);
        }
    }
    return true;
}

void TankJoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto orilocation = Director::getInstance()->convertToGL((touch->getLocationInView()));
    auto location = convertToNodeSpaceAR(orilocation);
    //CCLOG("move to,oriPos(%f,%f),pos:(%f,%f)",orilocation.x,orilocation.y,location.x,location.y);
    updateVelocity(location);
}

void TankJoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    thumb->setPosition(centerPos);
    stickMovePos = Vec2(0,0);
}

void TankJoyStick::update(float dt)
{
    thumb->setPosition(stickMovePos+centerPos);
}