//
//  EnemyTank.cpp
//  Tank
//
//  Created by wwj on 14/11/17.
//
//

#include "EnemyTank.h"
#include "GameDefine.h"
#include "EnemyTankGun.h"

bool EnemyTank::initWithValue(const char* body,const char* gun,int index,int blood)
{
    enemyTankSize = Size(80,80);
    setContentSize(enemyTankSize);
    
    enemyTankBody = Sprite::create(body);
    addChild(enemyTankBody);
    
    enemyTankGun = EnemyTankGun::create(gun, index);
    enemyTankGun->setAnchorPoint(Vec2(0.5,0.27));
    enemyTankGun->setRotation(180);
    addChild(enemyTankGun);
    
    tankIndex = index;
    enemyTankBlood = blood;
    isEnemyAnimation = false;
    return true;
}

bool EnemyTank::isCollision(Sprite* tankBullet)
{
    auto bulletPos = tankBullet->getPosition();
    auto mypos = getPosition();
    float width = tankBullet->getContentSize().width+getContentSize().width;
    float height = tankBullet->getContentSize().height+getContentSize().height;
    
    if (abs(bulletPos.x-mypos.x) < width/2 || abs(bulletPos.y-mypos.y) < height/2)
        return true;
    else
        return false;
}

void EnemyTank::rotateGun(float angle)
{
    auto rotateAct = RotateTo::create(0.3, angle);
    enemyTankGun->runAction(rotateAct);    
}

float EnemyTank::getEnemyTankGunRotation()
{
    return enemyTankGun->getRotation();
}

Vec2 EnemyTank::getEnemyTankGunPos()
{
    return enemyTankGun->getPosition();
}