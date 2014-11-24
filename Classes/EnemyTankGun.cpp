//
//  EnemyTankGun.cpp
//  Tank
//
//  Created by wwj on 14/11/23.
//
//

#include "EnemyTankGun.h"

EnemyTankGun* EnemyTankGun::create(const char *filename, int index)
{
    EnemyTankGun* gun = new EnemyTankGun;
    if (!gun->initWithFile(filename, Rect(0,0,33,68))) {
        CC_SAFE_DELETE(gun);
        return NULL;
    }
    
    gun->enemyTankIndex = index;
    
    return gun;
}