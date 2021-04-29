/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "scene101.h"
#include "scene102.h"
#include "SimpleAudioEngine.h"

extern cocos2d::Size fSize;

#define HOME_BACKGROUND "scene101/s101bgimg.png"

USING_NS_CC;

Scene* Scene102::createScene()
{
    return Scene102::create();
}

Scene102::Scene102() {
    bean01 = nullptr;
    _bBean01 = false;
}
Scene102::~Scene102() {
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("scene101/scene101.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("scene101/scene101bg.plist");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scene102::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene101/scene101.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene101/scene101bg.plist");

    /////////////////////////////
    // 2. 增加場景中的物件
    // 2. add a menu item with "X" image, which is clicked to quit the program you may modify it.
    //以 Sprite 作為背景
    //Sprite* bkimage = Sprite::create(HOME_BACKGROUND);  // 使用 create 函式,給予檔名即可
    Sprite* bkimage = Sprite::createWithSpriteFrameName("s101bgimg.png");
    bkimage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)); // 位置通常放置在螢幕正中間
    this->addChild(bkimage, 0);

    // 自行增加 sprite 將 bean01.png 到螢幕正中間
    bean01 = Sprite::create("scene101/bean01.png");  // 使用 create 函式,給予檔名即可
    bean01->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)); // 位置通常放置在螢幕正中間
    this->addChild(bean01, 1);
    auto size = bean01->getContentSize();
    Point pos = bean01->getPosition();
    this->bean01_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
    /////////////////////////////
    // 3. add your codes below...


// 文字的加入
    // label 使用 TTF 與 BitMap Font
    std::ostringstream ostr;
    ostr << static_cast<int>(fSize.width);
    std::string buffer = ostr.str();
    auto labelTTF = Label::createWithTTF(buffer, "fonts/Marker Felt.ttf", 32);
    labelTTF->setAlignment(cocos2d::TextHAlignment::CENTER); // 預設靠左對齊
    labelTTF->setWidth(100);	// 設定每行文字的顯示寬度
    size = labelTTF->getContentSize();
    labelTTF->setPosition(Vec2(origin.x + visibleSize.width - size.width / 2 - 10, origin.y + visibleSize.height - size.height / 2 - 10));
   
    
    this->addChild(labelTTF, 1);

    //一般(非中文字)文字的顯示方式
 //   auto labelBMF = Label::createWithBMFont("fonts/couriernew32.fnt", "Scene 102");
    ostr.str(""); // 設定字串為 null
    this->_sceneno = 102;  ostr << _sceneno;
    _strSceneNo = ostr.str();
    labelBMF = Label::createWithBMFont("fonts/couriernew32.fnt", _strSceneNo);

    size = labelBMF->getContentSize();
    labelBMF->setColor(Color3B::WHITE);
    labelBMF->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - size.height));
    this->addChild(labelBMF, 1);

    // 中文字的顯示方式
    auto strings = FileUtils::getInstance()->getValueMapFromFile("scene101/strings.xml");
    std::string str1 = strings["text1"].asString();
    std::string str2 = strings["text2"].asString();
    std::string str3 = strings["text3"].asString();
    auto labelchi1 = Label::createWithBMFont("fonts/msblack56.fnt", str1);
    auto labelchi2 = Label::createWithBMFont("fonts/msblack56.fnt", str2);
    auto labelchi3 = Label::createWithBMFont("fonts/msblack56.fnt", str3);
    size = labelchi1->getContentSize();
    labelchi1->setColor(Color3B(255, 238, 217));
    labelchi1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 80 - size.height));
    this->addChild(labelchi1, 1);

    labelchi2->setColor(Color3B(238, 255, 227));
    size = labelchi2->getContentSize();
    labelchi2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 140 - size.height));
    this->addChild(labelchi2, 1);

    labelchi3->setColor(Color3B(238, 255, 227));
    size = labelchi3->getContentSize();
    labelchi3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 200 - size.height));
    this->addChild(labelchi3, 1);
  
// Touch 與 Button 的處理
    // add Return Button
    this->btn_return = Sprite::create("scene101/returnbtn.png");
    size = btn_return->getContentSize();
    this->btn_return->setPosition(Vec2(origin.x + size.width / 2 + 5, origin.y + visibleSize.height - size.height / 2 - 5));
    pos = btn_return->getPosition();
    this->return_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
    this->addChild(btn_return, 1);

    // add Replay Button
    this->btn_replay = Sprite::create("scene101/replaybtn.png");
    size = btn_replay->getContentSize();
    this->btn_replay->setPosition(Vec2(origin.x + size.width / 2 + 90, origin.y + visibleSize.height - size.height / 2 - 5));
    pos = btn_replay->getPosition();
    this->replay_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
    this->addChild(btn_replay, 1);

    // add Cuber Button
    this->btn_cuber = Sprite::create("scene101/cuberbtn1.png");
    size = btn_cuber->getContentSize();
    this->btn_cuber->setPosition(Vec2(origin.x + visibleSize.width - size.width / 2, origin.y + visibleSize.height - size.height / 2 - 60));
    pos = btn_cuber->getPosition();
    this->cuber_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
    this->addChild(btn_cuber, 1);

    //this->_sceneno = 101;
    //strcpy(this->_cSceneNo, "Scene 101");

    //創建一個一對一的事件聆聽器
    auto listener = EventListenerTouchOneByOne::create();	
    listener->onTouchBegan = CC_CALLBACK_2(Scene102::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Scene102::onTouchMoved, this);//加入觸碰移動事件
    listener->onTouchEnded = CC_CALLBACK_2(Scene102::onTouchEnded, this);//加入觸碰離開事件


    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);	//加入剛創建的事件聆聽器
    this->schedule(CC_SCHEDULE_SELECTOR(Scene102::update));

 //   schedule(CC_SCHEDULE_SELECTOR(Scene102::update));

    return true;
}

void Scene102::update(float dt)
{

}
//
//void Scene102::menuCloseCallback(Ref* pSender)
//{
//    //Close the cocos2d-x game scene and quit the application
//    Director::getInstance()->end();
//
//    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
// }

bool Scene102::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();
    if (cuber_rect.containsPoint(touchLoc)) {

    }
    if (replay_rect.containsPoint(touchLoc)) {

    }
    if (return_rect.containsPoint(touchLoc)) {
        auto scene = TransitionMoveInL::create(0.6f, Scene101::create());
        Director::getInstance()->replaceScene(scene);
        //unscheduleAllCallbacks();
        //Director::getInstance()->end();
    }
    if (bean01_rect.containsPoint(touchLoc)) {
        _bBean01 = true;
        pt_old = touchLoc;
    }
    std::ostringstream ostr;
    ostr << _sceneno++;
    _strSceneNo = ostr.str();
    labelBMF->setString(_strSceneNo);


  return true;
}


void Scene102::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent) //觸碰移動事件
{
    Point touchLoc = pTouch->getLocation();
    pt_cur = touchLoc;
    if (_bBean01) {
        Point t = pt_cur - pt_old;
        Point pos = this->bean01->getPosition()+t;
        this->bean01->setPosition(pos);
        auto size = bean01->getContentSize();
        this->bean01_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
        pt_old = pt_cur;
    }

}

void  Scene102::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent) //觸碰結束事件 
{
    Point touchLoc = pTouch->getLocation();
    if (bean01_rect.containsPoint(touchLoc)) {
        _bBean01 = false;
    }
}