//
//  ControlLayer.h
//  Tank
//
//  Created by wwj on 14/11/4.
//
//

#ifndef __Tank__ControlLayer__
#define __Tank__ControlLayer__

#include <stdio.h>
#include "cocos2d.h"
class TankJoyStick;
class GunJoyStick;
class GameScene;
using namespace cocos2d;

class ControlLayer: public Layer
{
public:
    CREATE_FUNC(ControlLayer);
    virtual bool init();
    
    void updateTank(float dt);
    void updateGun(float dt);
    void tankShoot(float dt);
    void addTankBullet();
    void removeTankBullet(Node* node);
    
    void setGameLayer(GameScene* l){gameLayer = l;}
    Vec2 calcPosition(Vec2 joyStickV);
    void clearGunMoveFlag(){gunMoveFlag = false;}
private:
    TankJoyStick* tankJoyStick;
    TankJoyStick* gunJoyStick;
    GameScene* gameLayer;
    Size winSize;
    bool gunMoveFlag;
};

#endif /* defined(__Tank__ControlLayer__) */
