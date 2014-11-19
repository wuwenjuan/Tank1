//
//  TankHp.h
//  Tank
//
//  Created by wwj on 14/11/1.
//
//

#ifndef __Tank__TankHp__
#define __Tank__TankHp__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

#define HP_LENTH 3
class TankHp : public Sprite
{
public:
    CREATE_FUNC(TankHp);
    virtual bool init();
    void addHp(unsigned short h);
    void reduceHp(short h);
    
private:
    int hp;
    Sprite* nums[HP_LENTH];
};
#endif /* defined(__Tank__TankHp__) */
