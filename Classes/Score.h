//
//  Score.h
//  Tank
//
//  Created by wwj on 14/11/1.
//
//

#ifndef __Tank__Score__
#define __Tank__Score__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

#define SCORE_LENGTH 5
class Score : public Sprite
{
public:
    CREATE_FUNC(Score);
    virtual bool init();
    void addScore(int s);
private:
    int score;
    Sprite* nums[SCORE_LENGTH];
};

#endif /* defined(__Tank__Score__) */
