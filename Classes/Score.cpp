//
//  Score.cpp
//  Tank
//
//  Created by wwj on 14/11/1.
//
//

#include "Score.h"

bool Score::init()
{
    if (!Sprite::init())
        return false;
    
    setContentSize(Size(100,100));
    
    Sprite* icon = Sprite::create("score_icon.png");
    icon->setPosition(0,0);
    addChild(icon);
    
    float numbeginX = icon->getTextureRect().size.width+10;
    for (int n=0; n<SCORE_LENGTH; ++n) {
        nums[SCORE_LENGTH-n-1] = Sprite::create("nums.png");
        nums[SCORE_LENGTH-n-1]->setPosition(numbeginX+30*n,0);
        nums[SCORE_LENGTH-n-1]->setTextureRect(Rect(0, 0, 30, 50));
        addChild(nums[SCORE_LENGTH-n-1]);
    }
    return true;
}

void Score::addScore(int s)
{
    score += s;
    
    for (int n=0; n<SCORE_LENGTH; ++n) {
        int value = 0;
        if (n==0) {
            value = score%10;
        }
        else
        {
            value = (int)(score/pow(10, n))%10;
        }
        nums[n]->setTextureRect(Rect(30*value, 0, 30, 50));
    }
}