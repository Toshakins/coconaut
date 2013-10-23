//
//  standard.h
//  coconaut
//
//  Created by Watta Puck on 10/22/13.
//
//

#ifndef coconaut_standard_h
#define coconaut_standard_h

//total number of tiles
const int tileNumber = 15;

//number of rows in game
const int rows = 4;

//gesture recognizer sensitivity
const int maxDelta = 60;

//tile size
const int size = 100;

typedef enum {
    Right = 1 << 0,
    Left  = 1 << 1,
    Up = 1 << 2,
    Down  = 1 << 3
}SwipeDirection;

#endif
