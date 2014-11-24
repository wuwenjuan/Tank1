//
//  EnemyTank.h
//  Tank
//
//  Created by wwj on 14/11/17.
//
//

#ifndef __Tank__EnemyTank__
#define __Tank__EnemyTank__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class EnemyTankGun;

class EnemyTank : public Sprite
{
public:
    CREATE_FUNC(EnemyTank);
    bool initWithValue(const char* body,const char* gun,int index,int blood);
    bool isCollision(Sprite* tankBullet);
    void rotateGun(float angle);
    int getEnemyTankIndex()const{return tankIndex;}
    float getEnemyTankGunRotation();
    Vec2 getEnemyTankGunPos();
public:
    Sprite* enemyTankBody;
    EnemyTankGun* enemyTankGun;
private:
    int tankIndex;
    int enemyTankBlood;
    Size enemyTankSize;
    bool isEnemyAnimation;
};

#endif /* defined(__Tank__EnemyTank__) */
