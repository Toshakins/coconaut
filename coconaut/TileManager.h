//
//  tile.h
//  coconaut
//
//  Created by Watta Puck on 10/22/13.
//
//

#ifndef __coconaut__tile__
#define __coconaut__tile__

#include "cocos2d.h"
#include "standard.h"

using namespace cocos2d;

class TileManager {
    CCLayerColor *tiles[tileNumber];
    CCPoint pit;
    CCLayer *parentLayer;
    bool isMovable(SwipeDirection);
    bool generationMode = true;
public:
    CCLayerColor *tileFill(int);
    TileManager(CCLayer *);
    void moveTile(SwipeDirection);
    void shuffle();
    const bool & isGenerationMode() const {
        return generationMode;
    }
    void setGenerationMode(const bool & b) {
        generationMode = b;
    }
};

#endif /* defined(__coconaut__tile__) */
