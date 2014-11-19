//
//  TankHp.cpp
//  Tank
//
//  Created by wwj on 14/11/1.
//
//

#include "TankHp.h"

bool TankHp::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    setContentSize(Size(150,50));
    auto hpImage = Sprite::create("redbox.png");
    hpImage->setPosition(30,0);
    addChild(hpImage);
    
    
    for(int n=0;n<HP_LENTH;++n)
    {
        nums[HP_LENTH-n-1] = Sprite::create("nums.png");
        nums[HP_LENTH-n-1]->setPosition(80+n*30,0);
        nums[HP_LENTH-n-1]->setTextureRect(Rect(0,0,30,50));
        addChild(nums[HP_LENTH-n-1]);
    }
    
    hp = 0;
    addHp(100);
    return true;
}

void TankHp::addHp(unsigned short h)
{
    hp += h;
    for(int n=0;n<HP_LENTH;++n)
    {
        int value = 0;
        if (n==0) {
            value = hp%10;
        }
        else{
            value = (int)(hp/pow(10, n))%10;
        }
        nums[n]->setTextureRect(Rect(30*value, 0, 30, 50));
    }
}

void TankHp::reduceHp(short h)
{
    
}