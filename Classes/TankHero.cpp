//
//  TankHero.cpp
//  Tank
//
//  Created by wwj on 14/11/4.
//
//

#include "TankHero.h"
#include "ControlLayer.h"
#include "GameScene.h"

bool TankHero::init()
{
    if (!Sprite::init())
        return false;
    
    setContentSize(Size(100,100));
    
    tankBody = Sprite::create("mainbody.png");
    tankBody->setPosition(0,0);
    addChild(tankBody, Game_Scene_Layer_TankBody);
    
    tankGun = Sprite::create("maingun.png",Rect(0,0,33,68));
    tankGun->setAnchorPoint(Vec2(0.5,0.27));
    tankGun->setPosition(0,0);
    addChild(tankGun,Game_Scene_Layer_TankGun);
    return true;
}

void TankHero::rotateTankBody(float angle)
{
    tankBody->setRotation(angle);
}

void TankHero::rotateTankGun(float angle)
{
    auto func = CallFunc::create(CC_CALLBACK_0(TankHero::clearGunMoveFlag, this));
    auto sequence = Sequence::create(RotateTo::create(0.15f, angle),func, NULL);
    tankGun->runAction(sequence);
}

void TankHero::clearGunMoveFlag()
{
    GameScene* parent = (GameScene*)getParent();
    parent->getControlLayer()->clearGunMoveFlag();
}

float TankHero::getGunRotation()
{
    return tankGun->getRotation();
}

Vec2 TankHero::getGunPosition()const
{
    return convertToWorldSpace(tankGun->getPosition());
    //return tankGun->getPosition();
}