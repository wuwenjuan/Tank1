//
//  EnemyTankGun.h
//  Tank
//
//  Created by wwj on 14/11/23.
//
//

#ifndef __Tank__EnemyTankGun__
#define __Tank__EnemyTankGun__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class EnemyTankGun : public Sprite
{
public:
    static EnemyTankGun* create(const char* filename,int index);
    int getEnemyTankIndex()const{return enemyTankIndex;}
private:
    int enemyTankIndex;
};

#endif /* defined(__Tank__EnemyTankGun__) */
