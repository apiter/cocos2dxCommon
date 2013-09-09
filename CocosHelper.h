//
//  CocosHelper.h
//  Burgers
//
//  Created by tanshoumei on 13-6-26.
//
//

#ifndef Burgers_CocosHelper_h
#define Burgers_CocosHelper_h

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

namespace CocosHelper {
    /*
     根据ccbi文件，生成CCNode.
     pCCBFileName: ccbi文件名
     pCCNodeName: 此CCNode注册的名字，
     **/
    static CCNode* openCcbNode(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader)
    {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        if(pCCNodeName != NULL && pCCNodeLoader != NULL) {
            ccNodeLoaderLibrary->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
        }
        cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
        ccbReader->autorelease();    
        CCNode * node = ccbReader->readNodeGraphFromFile(pCCBFileName);        
        return node;
    }
    /*
     从CCAniamte中获取CCSprite
     aFrameInx: 帧索引，返回相应的帧生成CCSprite。
     **/
    static CCSprite* getSpriteFromAnimate( const CCAnimate* apAni, const int aFrameInx = 0)
    {
        CCSprite* pRet = NULL;
        if( apAni )
        {
            CCArray * pFrames = apAni->getAnimation()->getFrames();
            if(pFrames && pFrames->count() > aFrameInx )
            {
                CCSpriteFrame* pFrame = ((CCAnimationFrame*)(pFrames->objectAtIndex(0)))->getSpriteFrame();
                pRet = CCSprite::createWithSpriteFrame(pFrame);
            }          
        }
        return pRet;
    }
    
    inline void CCNodePositionYAdd( CCNode* apTarget, const float deltaY )
    {
        if(apTarget)
            apTarget->setPositionY( apTarget->getPositionY() + deltaY );
    }
    
    inline void CCNodePositionXAdd( CCNode* apTarget, const float delta )
    {
        if(apTarget)
            apTarget->setPositionX( apTarget->getPositionX() + delta );
    }
    
    inline void AddNode(CCNode* apNode, CCNode* apParent, const CCPoint& aPt, const int aZorder, const int aTag)
    {
        if(apNode && apParent)
        {
            apParent->addChild(apNode, aZorder, aTag);
            apNode->setPosition(aPt);
        }
    }
    
    inline CCSprite* AddSprite( const char* apFileName, CCNode* apParent, const CCPoint& aPt, const int aZorder, const int aTag)
    {
        CCSprite *spr = CCSprite::create(apFileName);
        AddNode(spr, apParent, aPt, aZorder, aTag);
        return spr;
    }
    
    inline CCSprite* AddSpriteByFrame( const char* apFileName, CCNode* apParent, const CCPoint& aPt, const int aZorder, const int aTag)
    {
        CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(apFileName);
        if(pFrame)
        {
            CCSprite* spr = CCSprite::createWithSpriteFrame(pFrame);
            AddNode(spr, apParent, aPt, aZorder, aTag);
            return spr;
        }
        return NULL;
    }
    
    inline CCRect stringToRect(std::string aStr, const char* sp = ",")
    {
        int nums[4] = {0};
        const char *tokenPtr = strtok((char*)aStr.c_str(), sp);
        int inx = 0;
        while (NULL != tokenPtr && inx < 4) {
            nums[inx++] = atoi(tokenPtr);
            tokenPtr = strtok(NULL, sp);
        }
        return CCRectMake(nums[0], nums[1], nums[2], nums[3]);
    }
    
    inline CCPoint stringToPoint(std::string aStr, const char* sp = ",")
    {
        int nums[2] = {0};
        const char *tokenPtr = strtok((char*)aStr.c_str(), sp);
        int inx = 0;
        while (NULL != tokenPtr && inx < 2) {
            nums[inx++] = atoi(tokenPtr);
            tokenPtr = strtok(NULL, sp);
        }
        return CCPointMake(nums[0], nums[1]);
    }
    
    //判断点是否在node之内，可用于touch判断
    inline bool isPointInNode(CCNode* apNode, const CCPoint& aPtWorld)
    {
        if(apNode)
        {
            CCRect rect;
            rect.origin = apNode->convertToWorldSpace(CCPointZero);
            rect.size = apNode->getContentSize();
            if(rect.containsPoint(aPtWorld))
                return true;
        }
        return false;
    }
    inline CCRect getNodeRectInWorld(CCNode* apNode)
    {
        CCRect rect;
        rect.origin = apNode->convertToWorldSpace(CCPointZero);
        rect.size = apNode->getContentSize();
        return rect;
    }
    //node content rect center
    inline CCPoint getNodeCenterLocal(CCNode* apNode)
    {
        CCPoint pt;
        if(apNode){
            pt.x = apNode->getContentSize().width * .5;
            pt.y = apNode->getContentSize().height * .5;
        }
        return pt;
    }
    
    //根据一张图，生成一个按钮item,其选中效果为变暗，和UIButton差不多
    inline CCMenuItemSprite* menuItemSprite(const char* aName)
    {
        CCSprite* normalSpr = CCSprite::create(aName);
        CCSprite* selectSpr = CCSprite::create(aName);
        selectSpr->setColor(ccGRAY);
        CCMenuItemSprite* item = CCMenuItemSprite::create(normalSpr, selectSpr);
        return item;
    }

    //当前系统时间(毫秒)
    inline long milliSecondNow()
    {
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        return (now.tv_sec * 1000 + now.tv_usec / 1000);
    }
}

#endif
