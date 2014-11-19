//
//  TankHero.h
//  Tank
//
//  Created by wwj on 14/11/4.
//
//

#ifndef __Tank__TankHero__
#define __Tank__TankHero__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;


enum Game_Scene_Layer
{
    Game_Scene_Layer_TankBody,
    Game_Scene_Layer_TankGun,
};

class TankHero : public Sprite
{
public:
    CREATE_FUNC(TankHero);
    virtual bool init();
    void rotateTankBody(float angle);
    void rotateTankGun(float angle);
    void clearGunMoveFlag();
    float getGunRotation();
    Vec2 getGunPosition()const;
public:
    Sprite* tankBody;
    Sprite* tankGun;
};

#endif /* defined(__Tank__TankHero__) */
