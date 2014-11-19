//
//  ControlLayer.cpp
//  Tank
//
//  Created by wwj on 14/11/4.
//
//

#include "ControlLayer.h"
#include "TankJoyStick.h"
#include "GameScene.h"
#include "TankHero.h"
#include "GameDefine.h"

bool ControlLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    winSize = Director::getInstance()->getWinSize();

    tankJoyStick = TankJoyStick::create();
    auto tankJoyStickSize = tankJoyStick->getContentSize();
    tankJoyStick->setPosition(tankJoyStickSize.width/2,tankJoyStickSize.height/2);
    addChild(tankJoyStick);
    
    gunJoyStick = TankJoyStick::create();
    auto gunJoyStickSize = gunJoyStick->getContentSize();
    gunJoyStick->setPosition(winSize.width-gunJoyStickSize.width/2,gunJoyStickSize.height/2);
    addChild(gunJoyStick);
    
    gunMoveFlag = false;
    
    schedule(schedule_selector(ControlLayer::updateTank));
    schedule(schedule_selector(ControlLayer::updateGun), 0.05f);
    schedule(schedule_selector(ControlLayer::tankShoot), 0.15);
    return true;
}

void ControlLayer::updateTank(float dt)
{
    if (gameLayer == NULL) {
        return;
    }
    
    Vec2 tankPosition = gameLayer->hero->getPosition();
    auto tankSize = gameLayer->hero->getContentSize();
    auto joyStickV = tankJoyStick->getVelocity();
    float tankAngle = 0;
    
    if (joyStickV.x == 0 && joyStickV.y ==0) {
        if (tankPosition.y-1 > tankSize.height/2) {
            gameLayer->hero->setPosition(tankPosition.x,tankPosition.y-1);
        }
        return;
    }
    
    if (joyStickV.x >0) {
        tankAngle = 90-atan(joyStickV.y/joyStickV.x)*180.0/pi;
    }
    else
    {
        tankAngle = -atan(joyStickV.y/joyStickV.x)*180/pi-90;
    }
    Vec2 newTankPos = calcPosition(joyStickV);
    gameLayer->hero->rotateTankBody(tankAngle);
    gameLayer->hero->setPosition(newTankPos);
    //CCLOG("tank move,angle:%f,newpos(%f,%f)",tankAngle,newTankPos.x,newTankPos.y);
}

Vec2 ControlLayer::calcPosition(Vec2 joyStickV)
{
    Vec2 tankPosition = gameLayer->hero->getPosition();
    auto tankSize = gameLayer->hero->getContentSize();

    float hx = tankPosition.x + (3+4)/2*joyStickV.x;
    float hy = tankPosition.y + (3+4)/2*joyStickV.y;
    
    Vec2 tpos = Vec2(hx,hy);
    if (hx < (tankSize.width/2) || hx>(winSize.width-tankSize.width/2)) {
        tpos.x = tankPosition.x;
    }
    if (hy<tankSize.height/2 || hy>(winSize.height-tankSize.height/2)) {
        tpos.y = tankPosition.y;
    }
    return tpos;
}

void ControlLayer::updateGun(float dt)
{
    if (gunMoveFlag) {
        return;
    }
    
    Vec2 gunJoyStickV = gunJoyStick->getVelocity();
    if (gunJoyStickV.x==0 && gunJoyStickV.y==0) {
        return;
    }
    gunMoveFlag = true;
    float gunAngle = 0;
    
    if (gunJoyStickV.x >0) {
        gunAngle = 90-atan(gunJoyStickV.y/gunJoyStickV.x)*180/pi;
    }
    else
    {
        gunAngle = -atan(gunJoyStickV.y/gunJoyStickV.x)*180/pi-90;
    }
    gameLayer->hero->rotateTankGun(gunAngle);
}

void ControlLayer::tankShoot(float dt)
{
    auto delayAct = DelayTime::create(0.2);
    auto animaAct = Animate::create(gameLayer->tankGunAnimation[0]);
    auto funcAct = CallFunc::create(CC_CALLBACK_0(ControlLayer::addTankBullet, this));
    auto seq = Sequence::create(delayAct, animaAct, funcAct,NULL);
    gameLayer->hero->tankGun->runAction(seq);
}

void ControlLayer::addTankBullet()
{
    Sprite* tankBullet = Sprite::create("tankBullet.png");
    float gunAngle = gameLayer->hero->getGunRotation();
    tankBullet->setRotation(gunAngle);
    gunAngle = gunAngle*pi/180.0;
    
    Vec2 gunPos = gameLayer->hero->getGunPosition();
    tankBullet->setPosition(gunPos.x+40*sin(gunAngle),gunPos.y+40*cos(gunAngle));
    
    auto moveAct = MoveTo::create(4, Vec2(gunPos.x+1600*sin(gunAngle),gunPos.y+800*cos(gunAngle)));
    auto funcAct = CallFuncN::create(CC_CALLBACK_1(ControlLayer::removeTankBullet,this));
    Sequence* seq = Sequence::create(moveAct,funcAct,NULL);
    tankBullet->runAction(seq);
    
    gameLayer->tankBullet->addChild(tankBullet);
}

void ControlLayer::removeTankBullet(Node* node)
{
    gameLayer->tankBullet->removeChild((Sprite*)node, true);
}

