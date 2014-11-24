//
//  Barrier.h
//  Tank
//
//  Created by wwj on 14/11/19.
//
//

#ifndef __Tank__Barrier__
#define __Tank__Barrier__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class Barrier : public Sprite
{
public:
    static Barrier* create(const char* pic,int index,int blood);
    bool isCollision(Sprite* target);
    int getBarrierIndex()const{return index;}
private:
    int index;
    int blood;
};

#endif /* defined(__Tank__Barrier__) */
