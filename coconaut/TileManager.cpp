//
//  tile.cpp
//  coconaut
//
//  Created by Watta Puck on 10/22/13.
//
//

#include "TileManager.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>
#include <string>

using namespace cocos2d;

CCLayerColor* TileManager::tileFill(int n) {
    CCLayerColor *tileBack = CCLayerColor::create(ccc4(255, 255, 255, 255), size, size);
    CCLabelTTF *tileText = CCLabelTTF::create(std::to_string(n + 1).c_str(), "Thonburi", 36.0, CCSize(size, size), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    
    CCSize winSize = parentLayer->getContentSize();
    tileBack->setPosition(ccp(n % rows * size, winSize.height - (n / rows + 1)  * size));
    parentLayer->addChild(tileBack);
    
    tileText->setPosition(ccp(0, 0));
    tileText->setFontFillColor(ccc3(0, 0, 0), true);
    tileText->setAnchorPoint(ccp(0, 0));
    tileBack->addChild(tileText);
    return tileBack;
}

void TileManager::moveTile(SwipeDirection d) {
    if (isMovable(d)) {
        CCLOG("Movable");
        //find tile to be moved
        CCPoint target = pit;
        CCLOG("Current.x: %f\nCurrent.y: %f", target.x, target.y);
        switch (d) {
            case Left:
                target.x += size;
                break;
            case Right:
                target.x -= size;
                break;
            case Up:
                target.y -= size;
                break;
            case Down:
                target.y += size;
            default:
                break;
        }
        CCLOG("Target.x: %f\nTarget.y: %f", target.x, target.y);
        int i = 0;
        for (; i < tileNumber; ++i) {
            CCLog("%d Candidate.x: %f\nCandidate.y: %f", i, tiles[i]->getPositionX(), tiles[i]->getPositionY());
            if (target.x == tiles[i]->getPositionX() && target.y == tiles[i]->getPositionY()) {
                CCLOG("Target found");
                CCPoint fakePit = tiles[i]->getPosition();
                if (isGenerationMode()) {
                    tiles[i]->setPosition(pit);
                }
                else {
                    tiles[i]->runAction(CCMoveTo::create(0.25, pit));
                }
                pit = fakePit;
                break;
            }
        }
    }
}

bool TileManager::isMovable(SwipeDirection d){
    switch (d) {
        case Left:
            return (pit.x + size== parentLayer->getContentSize().width) ? false : true;
            break;
        case Right:
            return (pit.x == 0) ? false : true;
            break;
        case Up:
            return (pit.y == 0) ? false : true;
            break;
        case Down:
            return (pit.y == parentLayer->getContentSize().height) ? false : true;
            break;
        default:
            break;
    }
    return false;
}

TileManager::TileManager(CCLayer * layer) {
    parentLayer = layer;
    for (int i = 0; i < tileNumber; ++i) {
        tiles[i] = tileFill(i);
    }
    pit = ccp((rows - 1) * size, 0);
}

void TileManager::shuffle() {
    int choice[4] = {Left, Right, Up, Down};
    srand(time(NULL));
    setGenerationMode(true);
    for (int i = 0; i < 100; ++i) {
        SwipeDirection x = (SwipeDirection)choice[rand() % 4];
        moveTile(x);
    }
    setGenerationMode(false);
}
