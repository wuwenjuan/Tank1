//
//  TankJoyStick.h
//  Tank
//
//  Created by wwj on 14/11/4.
//
//

#ifndef __Tank__TankJoyStick__
#define __Tank__TankJoyStick__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class TankJoyStick : public Sprite
{
public:
    CREATE_FUNC(TankJoyStick);
    virtual bool init();
    virtual void update(float dt);
    Vec2 getVelocity()const{return velocity;}
    void updateVelocity(Vec2 point);
    
    bool onTouchBegin(Touch* touch,Event* event);
    void onTouchMoved(Touch* touch,Event* event);
    void onTouchEnded(Touch* touch,Event* event);
private:
    Vec2 velocity;
    float radius;
    float radiusSqr;
    Vec2 centerPos;
    Vec2 stickMovePos;
    Sprite* thumb;
};

#endif /* defined(__Tank__TankJoyStick__) */
