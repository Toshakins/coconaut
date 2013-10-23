#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "standard.h"

using namespace cocos2d;
using namespace CocosDenshion;

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    touchBegan = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    return true;
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    touchEnded = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCLOG("Start: %f %f\nEnd: %f %f", touchBegan.x, touchBegan.y, touchEnded.x, touchEnded.y);
    int deltaX = abs(touchBegan.x - touchEnded.x);
    int deltaY = abs(touchBegan.y - touchEnded.y);
    //alternatively, it could be implemented via vector algebra
    if (deltaY < maxDelta && deltaX > maxDelta) {
        //right
        if (touchBegan.x < touchEnded.x) {
            CCLOG("right\n");
            tileManager->moveTile(Right);
        }
        //left
        if (touchBegan.x > touchEnded.x){
            CCLOG("left\n");
            tileManager->moveTile(Left);
        }
    }
    if(deltaX < maxDelta && deltaY > maxDelta) {
        //up
        if (touchBegan.y < touchEnded.y) {
            CCLOG("up\n");
            tileManager->moveTile(Up);
        }
        //down
        if (touchBegan.y > touchEnded.y) {
            CCLOG("down\n");
            tileManager->moveTile(Down);
        }
    }
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //TODO: rewrite as CCLayer
    contentLayer = CCLayerColor::create(ccc4(0, 0, 0, 255), size * rows, size * rows);
    CCSize center = CCDirector::sharedDirector()->getWinSize();
    //setAnchorPoint doesn't work
    contentLayer->setPosition(ccp(center.width / 2 - size * 2, center.height / 2 - size * 2));
    tileManager = new TileManager(contentLayer);
    this->addChild(contentLayer);
    
    tileManager->shuffle();
    
    //setup touch responders
    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
