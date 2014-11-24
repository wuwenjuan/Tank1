//
//  GameScene.cpp
//  Tank
//
//  Created by wwj on 14/11/1.
//
//

#include "GameScene.h"
#include "TankHp.h"
#include "Score.h"
#include "ControlLayer.h"
#include "TankHero.h"
#include "GameDefine.h"
#include "EnemyTank.h"
#include "Barrier.h"
#include "EnemyTankGun.h"

Scene* GameScene::createScene()
{
    Scene* scene = Scene::create();

    auto layer = GameScene::create();
    scene->addChild(layer);

    auto controlLayer = ControlLayer::create();
    scene->addChild(controlLayer);
    controlLayer->setGameLayer(layer);
    layer->setControlLayer(controlLayer);
    
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    winsize = Director::getInstance()->getWinSize();
    
    initBackGroud();
    initHeroTank();
    
    //敌方子弹和炮弹
    enemyBullet = SpriteBatchNode::create("enemyBullet.png");
    addChild(enemyBullet,Game_Layer_Bullet);
    enemyBazooka = SpriteBatchNode::create("enemyBazooka.png");
    addChild(enemyBazooka,Game_Layer_Bullet);
    
    hp = TankHp::create();
    hp->setAnchorPoint(Vec2(0,0));
    hp->setPosition(0,winsize.height-50);
    addChild(hp,Game_Layer_BackGround);
    
    score = Score::create();
    score->setAnchorPoint(Vec2(0,0));
    score->setPosition(winsize.width/2,winsize.height-50);
    addChild(score);
    
    strncpy(pBName[0], "mark1.png", 32);
    strncpy(pBName[1], "tree1.png", 32);
    strncpy(pBName[2], "tree2.png", 32);
    
    trees = Node::create();
    addChild(trees,Game_Layer_Trees);
    marks = Node::create();
    addChild(marks,Game_Layer_Trees);
    
    addOneGroupTree();
    initGunAnimation();
    
    enemyName[0] = "enemyBullet.png";
    enemyName[1] = "enemyBullet.png";
    enemyName[2] = "enemyBazooka.png";
    enemyName[3] = "enemyBazooka.png";
    enemyName[4] = "enemyBazooka.png";
    
    schedule(schedule_selector(GameScene::updateBackGround), 0.04);
    schedule(schedule_selector(GameScene::addTrees),3);
    schedule(schedule_selector(GameScene::addEnemyTank), 2);
    schedule(schedule_selector(GameScene::updateEnemyTank), 0.05);
    schedule(schedule_selector(GameScene::enemyTankShoot), 1);

    return true;
}

void GameScene::initBackGroud()
{
    bg1 = Sprite::create("gameBackground.png");
    bg1->setAnchorPoint(Vec2(0,0));
    bg1->setPosition(0,0);
    auto textureSize = bg1->getTextureRect().size;
    bg1->setScale(winsize.width/textureSize.width, winsize.height/textureSize.height);
    addChild(bg1,Game_Layer_BackGround);
    
    bg2 = Sprite::create("gameBackground.png");
    bg2->setAnchorPoint(Vec2(0,0));
    bg2->setPosition(0,winsize.height-5);
    bg2->setScale(winsize.width/textureSize.width, winsize.height/textureSize.height);
    addChild(bg2,Game_Layer_BackGround);
}

#define BG_MOVE_SPEED 2
void GameScene::updateBackGround(float dt)
{
    bg1->setPosition(bg1->getPosition().x,bg1->getPosition().y-BG_MOVE_SPEED);
    bg2->setPosition(bg2->getPosition().x,bg2->getPosition().y-BG_MOVE_SPEED);
    
    if (bg1->getPosition().y < 0) {
        bg2->setPosition(bg1->getPosition().x,bg1->getPosition().y+winsize.height-5);
    }
    
    if (bg2->getPosition().y < 0) {
        bg1->setPosition(bg2->getPosition().x,bg2->getPosition().y+winsize.height-5);
    }
    
    Vector<Node*> treesVec = trees->getChildren();
    for (auto it=treesVec.begin(); it!=treesVec.end(); ++it) {
        Sprite* tree = (Sprite*)(*it);
        if (tree->getPosition().y < -100) {
            trees->removeChild(tree);
        }
    }
    
    Vector<Node*> marksVec = marks->getChildren();
    for (auto it=marksVec.begin(); it!=marksVec.end(); ++it) {
        Sprite* mark = (Sprite*)(*it);
        if (mark->getPosition().y < ENEMY_MIN_POS) {
            marks->removeChild(mark);
        }
    }
}

void GameScene::initHeroTank()
{
    hero = TankHero::create();
    hero->setPosition(400,200);
    addChild(hero,Game_Layer_Tank);
    
    tankBullet = SpriteBatchNode::create("tankBullet.png");
    addChild(tankBullet,Game_Layer_Bullet);
    
    tankBazooka = SpriteBatchNode::create("tankBazooka.png");
    addChild(tankBazooka);
}

void GameScene::addTrees(float dt)
{
    int index = rand()%3;
    auto treeOrMark = Sprite::create(pBName[index]);
    float x = rand()%(int)(winsize.width);
    float y = rand()%100+winsize.height+50;
    float time = y/winsize.height*20;
    treeOrMark->setPosition(x,y);
    treeOrMark->runAction(MoveTo::create(time, Vec2(x,ENEMY_MIN_POS)));
    
    if (index==0) {
        float scale = rand()%2+0.5;
        treeOrMark->setScale(scale);
        marks->addChild(treeOrMark);
    }
    else
        trees->addChild(treeOrMark);
}

void GameScene::addOneGroupTree()
{
    float x=0.0;
    float y=0.0;
    
    x = rand()%(int)(winsize.width);
    y = rand()%440+100;
    auto mark1 = Sprite::create("mark1.png");
    mark1->setPosition(x,y);
    mark1->setScale(2);
    mark1->runAction(MoveTo::create(20, Vec2(x,y-700)));
    marks->addChild(mark1);
    
    x = rand()%(int)(winsize.width);
    y = rand()%440+100;
    auto mark2 = Sprite::create("mark1.png");
    mark2->cocos2d::Node::setPosition(x,y);
    mark2->cocos2d::Node::setScale(2);
    float time = y/winsize.height*20;
    mark2->runAction(MoveTo::create(time, Vec2(x,ENEMY_MIN_POS)));
    marks->addChild(mark2);
    
    x = rand()%(int)(winsize.width);
    y = rand()%440+100;
    Sprite* back1 = Sprite::create("tree1.png");
    back1->cocos2d::Node::setPosition(x,y);
    time = y/winsize.height*20;
    back1->runAction(MoveTo::create(time, Vec2(x,ENEMY_MIN_POS)));
    trees->addChild(back1);
    
    x = rand()%(int)(winsize.width);
    y = rand()%440+100;
    Sprite* back2 = Sprite::create("tree2.png");
    time = y/winsize.height*20;
    back2->setPosition(x,y);
    back2->runAction(MoveTo::create(time, Vec2(x,ENEMY_MIN_POS)));
    trees->addChild(back2);
}

void GameScene::initGunAnimation()
{
    tankGunAnimation[0] = initGunAnimation("maingun.png");
    tankGunAnimation[1] = initGunAnimation("enemygun1.png");
    tankGunAnimation[2] = initGunAnimation("enemygun2.png");
    tankGunAnimation[3] = initGunAnimation("enemygun3.png");
    tankGunAnimation[4] = initGunAnimation("enemygun4.png");
}

Animation* GameScene::initGunAnimation(const char* pic)
{
    auto texture = Director::getInstance()->getTextureCache()->addImage(pic);
    auto sp1 = SpriteFrame::createWithTexture(texture, Rect(0,0,33,68));
    auto sp2 = SpriteFrame::createWithTexture(texture, Rect(33,0,33,68));
    
    Vector<SpriteFrame*> frames;
    frames.pushBack(sp1);
    frames.pushBack(sp2);
    auto anmi = Animation::createWithSpriteFrames(frames);
    anmi->setDelayPerUnit(0.07);
    anmi->retain();
    return anmi;
}

void GameScene::addEnemyTank(float dt)
{
    int index = rand()%10+1;
    switch (index) {
        case 1:
            addEnemyTankGroup1();
            break;
        case 2:
            addEnemyTankGroup2();
            break;
        case 3:
            addEnemyTankGroup3();
            break;
        case 4:
            addEnemyTankGroup4();
            break;
        case 5:
            addEnemyTankGroup5();
            break;
        case 6:
            addEnemyTankGroup6();
            break;
        case 7:
            addEnemyTankGroup7();
            break;
        case 8:
            addEnemyTankGroup8();
            break;
        case 9:
            addEnemyTankGroup9();
            break;
        case 10:
            addEnemyTankGroup10();
            break;
        default:
            break;
    }
}

void GameScene::addEnemyTank(Vec2 pos,const char* body,const char* gun,int index,int blood)
{
    auto enemytank = EnemyTank::create();
    enemytank->initWithValue(body, gun, index, blood);
    enemytank->setPosition(pos.x,pos.y+60);
    
    float movetime = (pos.y+60)/winsize.height*20;
    auto moveAct = MoveTo::create(movetime, Vec2(pos.x,ENEMY_MIN_POS));
    auto removeAct = CallFuncN::create(CC_CALLBACK_1(GameScene::removeEnemyTank, this));
    enemytank->runAction(Sequence::create(moveAct, removeAct, NULL));
    addChild(enemytank,Game_Layer_Tank);
    enemyTankVec.push_back(enemytank);
}

void GameScene::removeEnemyTank(Node* etank)
{
    this->removeChild(etank);
    enemyTankVec.erase(std::find(enemyTankVec.begin(), enemyTankVec.end(), etank));
}

void GameScene::addEnemyTankGroup1()
{
    addEnemyTank1(Vec2(winsize.width/8,winsize.height));
    addEnemyTank1(Vec2(winsize.width/8,winsize.height));
}

void GameScene::addEnemyTankGroup2()
{
    addEnemyTank2(Vec2(winsize.width/8,winsize.height));
    addEnemyTank2(Vec2(winsize.width/8*2,winsize.height));
    addEnemyTank1(Vec2(winsize.width/8*6,winsize.height));
    addEnemyTank1(Vec2(winsize.width/8*7,winsize.height));
}

void GameScene::addEnemyTankGroup3()
{
    addBarrier(Vec2(winsize.width/8*3,winsize.height));
    addBarrier(Vec2(winsize.width/8*4,winsize.height));
    addBarrier(Vec2(winsize.width/8*5,winsize.height));
    addTower(Vec2(winsize.width/8*4,winsize.height+100));
}

void GameScene::addEnemyTankGroup4()
{
    addBarrier(Vec2(winsize.width/8*1,winsize.height));
    addBarrier(Vec2(winsize.width/8*2,winsize.height));
    addBarrier(Vec2(winsize.width/8*3,winsize.height));
    addTower(Vec2(winsize.width/16*3,winsize.height+100));
    addEnemyTank2(Vec2(winsize.width/16*5,winsize.height+100));
    
    addBarrier(Vec2(winsize.width/8*5,winsize.height));
    addBarrier(Vec2(winsize.width/8*6,winsize.height));
    addBarrier(Vec2(winsize.width/8*7,winsize.height));
    addTower(Vec2(winsize.width/16*11,winsize.height+100));
    addEnemyTank2(Vec2(winsize.width/16*13,winsize.height+100));
}

void GameScene::addEnemyTankGroup5()
{
    addBarrier(Vec2(winsize.width/8*3,winsize.height));
    addBarrier(Vec2(winsize.width/8*5,winsize.height));
    addEnemyTank1(Vec2(winsize.width/8*4,winsize.height));
    addTower(Vec2(winsize.width/16*7,winsize.height+100));
    addTower(Vec2(winsize.width/16*9,winsize.height+100));
}

void GameScene::addEnemyTankGroup6()
{
    
}

void GameScene::addEnemyTankGroup7()
{
    
}

void GameScene::addEnemyTankGroup8()
{
    
}

void GameScene::addEnemyTankGroup9()
{
    
}

void GameScene::addEnemyTankGroup10()
{
    
}

void GameScene::addEnemyTank1(Vec2 pos)
{
    addEnemyTank(pos, "enemybody1.png", "enemygun1.png", 1, 1);
}

void GameScene::addEnemyTank2(Vec2 pos)
{
    addEnemyTank(pos, "enemybody2.png", "enemygun2.png", 2, 1);
}

void GameScene::addEnemyTank3(Vec2 pos)
{
    addEnemyTank(pos,"enemybody3.png","enemygun3.png", 3,2);
}

void GameScene::addEnemyTank4(Vec2 pos)
{
    addEnemyTank(pos,"enemybody4.png","enemygun4.png",4,2);
}

void GameScene::addBarrier(Vec2 pos)
{
    Barrier* barrier = Barrier::create("barrier.png", 6, 2);
    barrier->setPosition(pos.x,pos.y+60);
    float time = (pos.y+60)/winsize.height*20;
    auto moveAct = MoveTo::create(time, Vec2(pos.x,ENEMY_MIN_POS));
    auto funcAct = CallFuncN::create(CC_CALLBACK_1(GameScene::removeBarrier, this));
    barrier->runAction(Sequence::create(moveAct,funcAct,NULL));
    barrierVec.push_back(barrier);
    addChild(barrier,Game_Layer_Tank);
}

void GameScene::addTower(Vec2 pos)
{
    Barrier* barrier = Barrier::create("tower.png", 5, 2);
    barrier->setPosition(pos.x,pos.y+60);
    float time = (pos.y+60)/winsize.height*20;
    auto moveAct = MoveTo::create(time, Vec2(pos.x,ENEMY_MIN_POS));
    auto funcAct = CallFuncN::create(CC_CALLBACK_1(GameScene::removeBarrier, this));
    barrier->runAction(Sequence::create(moveAct,funcAct, NULL));
    barrierVec.push_back(barrier);
    addChild(barrier,Game_Layer_Tank);
}

void GameScene::removeBarrier(cocos2d::Node *barrier)
{
    barrierVec.erase(std::find(barrierVec.begin(), barrierVec.end(), barrier));
    removeChild(barrier);
}

void GameScene::updateEnemyTank(float dt)
{
    Vec2 heroPos = hero->getPosition();
    for (auto it=enemyTankVec.begin(); it!=enemyTankVec.end(); ++it) {
        Vec2 enemyPos = (*it)->getPosition();
        Vec2 tempdis = Vec2(heroPos.x-enemyPos.x,heroPos.y-enemyPos.y);
        float angle = 0.0;
        if (tempdis.x > 0) {
            angle = 90-atan(tempdis.y/tempdis.x)*180.0/pi;
        }
        else
        {
            angle = -atan(tempdis.y/tempdis.x)*180.0/pi-90;
        }
        (*it)->rotateGun(angle);
    }
}

void GameScene::enemyTankShoot(float dt)
{
    for (auto it=enemyTankVec.begin(); it!=enemyTankVec.end(); ++it) {
        EnemyTank* enemyTank = (EnemyTank*)(*it);
        int index = rand()%3;
        auto waitAct = DelayTime::create(index*0.005);
        Animate* aniAct = Animate::create(tankGunAnimation[enemyTank->getEnemyTankIndex()]);
        auto shootAct = CallFuncN::create(CC_CALLBACK_1(GameScene::addEnemyTankBullet, this));
        enemyTank->enemyTankGun->runAction(Sequence::create(waitAct,aniAct,shootAct, NULL));
    }
    
    for (auto it=barrierVec.begin(); it!=barrierVec.end(); ++it) {
        Barrier* barrier = (Barrier*)(*it);
        if (barrier->getBarrierIndex() == 5) {
            addBarrierBullet(barrier);
        }
    }
}

void GameScene::addEnemyTankBullet(Node* node)
{
    auto* enemyTankGun = (EnemyTankGun*)node;
    auto etankbullet = Sprite::create(enemyName[enemyTankGun->getEnemyTankIndex()-1].c_str());
    switch (enemyTankGun->getEnemyTankIndex()) {
        case 1:
        case 2:
            enemyBullet->addChild(etankbullet);
            break;
        case 3:
        case 4:
            enemyBazooka->addChild(etankbullet);
            break;
        default:
            break;
    }
    
    float enemyTankGunRotation = enemyTankGun->getRotation();
    etankbullet->setRotation(enemyTankGunRotation);
    enemyTankGunRotation = enemyTankGunRotation*pi/180.0f;
    
    Vec2 enemyTankGunPos = enemyTankGun->getPosition();
    enemyTankGunPos = enemyTankGun->convertToWorldSpaceAR(enemyTankGunPos);
    etankbullet->setPosition(enemyTankGunPos.x+40*sin(enemyTankGunRotation),enemyTankGunPos.y+40*cos(enemyTankGunRotation));
    
    auto moveAct = MoveTo::create(8, Vec2(enemyTankGunPos.x+1600*sin(enemyTankGunRotation),enemyTankGunPos.y+1200*cos(enemyTankGunRotation)));

    if (enemyTankGun->getEnemyTankIndex() < 3) {
        auto funcAct = CallFuncN::create(CC_CALLBACK_1(GameScene::removeEnemyTankBullet, this));
        etankbullet->runAction(Sequence::create(moveAct,funcAct, NULL));
    }
    else
    {
        auto funcAct = CallFuncN::create(CC_CALLBACK_1(GameScene::removeEnemyTankBazooka, this));
        etankbullet->runAction(Sequence::create(moveAct,funcAct, NULL));
    }
}

void GameScene::addBarrierBullet(Node* node)
{
    Barrier* barrier = (Barrier*)node;
    auto barrierBullet = Sprite::create(enemyName[barrier->getBarrierIndex()-1].c_str());
    enemyBazooka->addChild(barrierBullet);
    barrierBullet->setPosition(barrier->getPosition());
    
    float angle = 0.0;
    auto posDiff = Vec2(hero->tankBody->getPosition().x-barrier->getPosition().x,hero->tankBody->getPosition().y-barrier->getPosition().y);
    if (posDiff.x > 0) {
        angle = 90-atan(posDiff.y/posDiff.x)*180/pi;
    }
    else
    {
        angle = -atan(posDiff.y/posDiff.x)*180/pi-90;
    }
    auto moveAct = MoveTo::create(5, Vec2(barrier->getPosition().x+1024*posDiff.x,barrier->getPosition().y+800*posDiff.y));
    barrierBullet->setRotation(angle);
    auto funcAct = CallFuncN::create(CC_CALLBACK_1(GameScene::removeEnemyTankBazooka, this));
    barrierBullet->runAction(Sequence::create(moveAct,funcAct, NULL));
}

void GameScene::removeEnemyTankBullet(Node *node)
{
    enemyBullet->removeChild(node, true);
}

void GameScene::removeEnemyTankBazooka(Node *node)
{
    enemyBazooka->removeChild(node, true);
}