//
//  GameScene.h
//  Tank
//
//  Created by wwj on 14/11/1.
//
//

#ifndef __Tank__GameScene__
#define __Tank__GameScene__

#include <stdio.h>
#include "cocos2d.h"
class TankHp;
class Score;
class TankHero;
class ControlLayer;
class EnemyTank;
class Barrier;

using namespace cocos2d;


class GameScene : public Layer
{
public:
    CREATE_FUNC(GameScene);
    static Scene* createScene();
    virtual bool init();
    void initHeroTank();
    void initBackGroud();
    void setControlLayer(ControlLayer* l){controlLayer = l;}
    ControlLayer* getControlLayer()const{return controlLayer;}
    void updateBackGround(float dt);
    void addTrees(float dt);
    void addOneGroupTree();
    void initGunAnimation();
    Animation* initGunAnimation(const char*);
    
public:
    TankHero* hero;
    SpriteBatchNode* tankBullet;
    Animation *tankGunAnimation[5];

private:
    Size winsize;
    Sprite* bg1;
    Sprite* bg2;
    
    TankHp* hp;
    Score* score;

    SpriteBatchNode* tankBazooka;

    ControlLayer* controlLayer;
    
    char pBName[3][32];
    Node* trees;
    Node* marks;
    
//敌人tank
public:
    void addEnemyTank(float dt);
    void addEnemyTank(Vec2 pos,const char* body,const char* gun,int index,int blood);
    void removeEnemyTank(Node* etank);
    void updateEnemyTank(float dt);
    void enemyTankShoot(float dt);
    void addEnemyTankBullet(Node *node);
    void addBarrierBullet(Node* node);
    void removeEnemyTankBullet(Node *node);
    void removeEnemyTankBazooka(Node *node);
    
    void addEnemyTankGroup1();
    void addEnemyTankGroup2();
    void addEnemyTankGroup3();
    void addEnemyTankGroup4();
    void addEnemyTankGroup5();
    void addEnemyTankGroup6();
    void addEnemyTankGroup7();
    void addEnemyTankGroup8();
    void addEnemyTankGroup9();
    void addEnemyTankGroup10();
    
    void addEnemyTank1(Vec2 pos);
    void addEnemyTank2(Vec2 pos);
    void addEnemyTank3(Vec2 pos);
    void addEnemyTank4(Vec2 pos);

    void addBarrier(Vec2 pos);
    void addTower(Vec2 pos);
    void removeBarrier(Node* barrier);

private:
    std::string enemyName[5];
    
    std::vector<EnemyTank*> enemyTankVec;
    std::vector<Barrier*> barrierVec;
    SpriteBatchNode* enemyBullet;
    SpriteBatchNode* enemyBazooka;
};
#endif /* defined(__Tank__GameScene__) */
