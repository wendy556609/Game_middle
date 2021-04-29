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
#include "SimpleAudioEngine.h"


#define HOME_BACKGROUND "scene101/s101bgimg.png"

USING_NS_CC;

Scene* Scene101::createScene()
{
    return Scene101::create();
}

Scene101::Scene101() {
    _fire = nullptr;
    _trienemy = nullptr;
    _c3sButton = nullptr;
    _midObj = nullptr;
    background_1 = nullptr;
    _runner = nullptr;
    _bBean01 = false;
    _bean = nullptr;
    _enemy = nullptr;
}
Scene101::~Scene101() {
    CC_SAFE_DELETE(_runner);
    CC_SAFE_DELETE(_midObj);
    CC_SAFE_DELETE(_c3sButton);
    CC_SAFE_DELETE(_trienemy);
    CC_SAFE_DELETE(_fire);
    CC_SAFE_DELETE(_bean);
    CC_SAFE_DELETE(_enemy);
    this->removeAllChildren();
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("scene101.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("scene101bg.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gamescene.plist");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scene101::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto rootNode = CSLoader::createNode("mainscene.csb");
    this->addChild(rootNode); // 加入目前的 scene 中

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene101/scene101.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene101/scene101bg.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene101/gamescene.plist");

    /////////////////////////////
    // 2. 增加場景中的物件
    // 2. add a menu item with "X" image, which is clicked to quit the program you may modify it.

    // 自行增加 sprite 將 bean01.png 到螢幕正中間
    auto loctag = dynamic_cast<cocos2d::Node*>(rootNode->getChildByName("_runner"));
    loctag->setVisible(false);
    auto position = loctag->getPosition();
    _runner = new (std::nothrow) CRunner();
    _runner->init(position,*this,"runner_demo.csb", "collider",3);

    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("road00"));
    loctag->setVisible(false);
    position = loctag->getPosition();
    _midObj = new (std::nothrow) CMiddleObject();
    _midObj->init(position, *this, "road00");

    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("jumpButton"));
    loctag->setVisible(false);
    position = loctag->getPosition();
    _c3sButton = new (std::nothrow)C3SButton();
    _c3sButton->init(_c3sButton->BtnType::jumpBtn, position, *this, "jumpnormal", "jumpon");

    /*position = Vec2(200, _runner->getPosition().y);
    _enemy = new (std::nothrow)CTriEnemy();
    _enemy->init(position, *this, "triangle_node.csb", "triblock_1", 3);*/

    /*position = Vec2(200,165);
    _fire = new (std::nothrow)CFEnemy();
    _fire->init(position, *this, "fire.csb", "collider", 3);*/

    /*position = Vec2(200, _runner->getPosition().y);
    _bean = new (std::nothrow)CBEnemy();
    _bean->init(position, *this, "bean_jump.csb", "collider", 3);*/

    _enemy = new (std::nothrow)CEnemyNode();
    _enemy->init(*this, _runner->getPosition());
    
    _midObj->setSpeed(2);

    //bean01 = Sprite::create("scene101/bean01.png");  // 使用 create 函式,給予檔名即可
    //bean01->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)); // 位置通常放置在螢幕正中間
    //this->addChild(bean01, 1);
    //auto size = bean01->getContentSize();
    //Point pos = bean01->getPosition();
    //this->bean01_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
    /////////////////////////////
    // 3. add your codes below...
  
// Touch 與 Button 的處理
    // add Return Button
    //this->btn_return = Sprite::create("scene101/returnbtn.png");
    //auto size = btn_return->getContentSize();
    //this->btn_return->setPosition(Vec2(origin.x + size.width / 2 + 5, origin.y + visibleSize.height - size.height / 2 - 5));
    //auto pos = btn_return->getPosition();
    //this->return_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
    //this->addChild(btn_return, 1);

    //// add Replay Button
    //this->btn_replay = Sprite::create("scene101/replaybtn.png");
    //size = btn_replay->getContentSize();
    //this->btn_replay->setPosition(Vec2(origin.x + size.width / 2 + 90, origin.y + visibleSize.height - size.height / 2 - 5));
    //pos = btn_replay->getPosition();
    //this->replay_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
    //this->addChild(btn_replay, 1);

    //// add Cuber Button
    //this->btn_cuber = Sprite::create("scene101/cuberbtn1.png");
    //size = btn_cuber->getContentSize();
    //this->btn_cuber->setPosition(Vec2(origin.x + visibleSize.width - size.width / 2, origin.y + visibleSize.height - size.height / 2 - 60));
    //pos = btn_cuber->getPosition();
    //this->cuber_rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
    //this->addChild(btn_cuber, 1);

    //this->_sceneno = 101;
    //strcpy(this->_cSceneNo, "Scene 101");

    //創建一個一對一的事件聆聽器
    auto listener = EventListenerTouchOneByOne::create();	
    listener->onTouchBegan = CC_CALLBACK_2(Scene101::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Scene101::onTouchMoved, this);//加入觸碰移動事件
    listener->onTouchEnded = CC_CALLBACK_2(Scene101::onTouchEnded, this);//加入觸碰離開事件


    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);	//加入剛創建的事件聆聽器
    this->schedule(CC_SCHEDULE_SELECTOR(Scene101::update));

 //   schedule(CC_SCHEDULE_SELECTOR(Scene101::update));

    return true;
}

void Scene101::update(float dt)
{
    _midObj->update(dt);
    _runner->update(dt);
    _c3sButton->setEnable(_c3sButton->BtnType::jumpBtn, !_runner->_isJump);
    _enemy->update(dt);
    if (_runner->_isJump) {
        _enemy->setSpeed(2.25f);
        _midObj->setSpeed(2.25f);
    }
    else {
        _enemy->setSpeed(2);
        _midObj->setSpeed(2);
    }

    if (_enemy->checkCollider(*_runner)) {
        if (!_runner->_isHurt) {
            _runner->_isHurt = true;
            if (_runner->_isHurt) {
                log("hurt");
            }
        }
    }
    else {
        _runner->_isHurt = false;
    }
    //CCLOG("%d",_enemy->getCollider()->_colliderPos.y);
    /*if (_runner->OnColliderCheck(*_enemy->getCollider())) {
        if (!_runner->_isHurt) {
            _runner->_isHurt = true;
            if (_runner->_isHurt) {
                log("hurt");
            }
        }
    }
    else {
        _runner->_isHurt = false;
    }*/
    /*if (_runner->OnColliderCheck(*_bean->getCollider())) {
        if (!_runner->_isHurt) {
            _runner->_isHurt = true;
            if (_runner->_isHurt) {
                log("hurt");
            }
        }
    }
    else {
        _runner->_isHurt = false;
    }*/
}
//
//void Scene101::menuCloseCallback(Ref* pSender)
//{
//    //Close the cocos2d-x game scene and quit the application
//    Director::getInstance()->end();
//
//    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
// }

bool Scene101::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();
    if (cuber_rect.containsPoint(touchLoc)) {

    }
    if (replay_rect.containsPoint(touchLoc)) {

    }
    if (return_rect.containsPoint(touchLoc)) {
        unscheduleAllCallbacks();
        Director::getInstance()->end();
    }
    if (_runner->getCollider()->_range.containsPoint(touchLoc)) {
        _bBean01 = true;
        pt_old = touchLoc;
        _runner->setState(_runner->State::happy);
        _runner->changeFace();
    }
    if (_c3sButton->touchesBegin(_c3sButton->BtnType::jumpBtn, touchLoc)) {
        _runner->_isJump = true;
    }
    if (_enemy->getCollider()->_range.containsPoint(touchLoc)) {
        log("touch");
    }

  return true;
}


void Scene101::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent) //觸碰移動事件
{
    Point touchLoc = pTouch->getLocation();
    pt_cur = touchLoc;
    if (_bBean01) {
        Point t = pt_cur - pt_old;
        Point pos = this->_runner->getPosition()+t;
        _runner->setPosition(pos);
        pt_old = pt_cur;
    }
    _c3sButton->touchesMove(_c3sButton->BtnType::jumpBtn,touchLoc);
}

void  Scene101::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent) //觸碰結束事件 
{
    Point touchLoc = pTouch->getLocation();
    if (_runner->getCollider()->_range.containsPoint(touchLoc)) {
        _bBean01 = false;
        _runner->setState(_runner->State::normal);
        _runner->changeFace();
    }
    if (_c3sButton->touchesEnd(_c3sButton->BtnType::jumpBtn, touchLoc)) {
        
    };
    
}