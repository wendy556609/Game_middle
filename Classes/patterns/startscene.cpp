#include "startscene.h"

USING_NS_CC;

StartScene::StartScene() {
    btn = nullptr;
}

StartScene::~StartScene() {
    CC_SAFE_DELETE(btn);
    this->removeAllChildren();
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("startscene.plist");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

Scene* StartScene::createScene()
{
    return StartScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartScene::init() {
    if (!Scene::init()) { return false; }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto rootNode = CSLoader::createNode("/startscene.csb");
    this->addChild(rootNode);

    auto btnLoc = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("startbtn"));
    btnLoc->setVisible(false);

    btn = new (std::nothrow)C3SButton();
    btn->init(btn->BtnType::startBtn, btnLoc->getPosition(), *this, "startnormal", "starton");

    //創建一個一對一的事件聆聽器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(StartScene::onTouchMoved, this);//加入觸碰移動事件
    listener->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded, this);//加入觸碰離開事件

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);	//加入剛創建的事件聆聽器
    this->schedule(CC_SCHEDULE_SELECTOR(StartScene::update));

    return true;
}

void StartScene::update(float dt) {
    if (_bToGameScene) {
        /*this->unschedule(schedule_selector(StartScene::update));
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("startscene.plist");*/
    }
}

bool StartScene::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();
    btn->touchesBegin(btn->BtnType::startBtn,touchLoc);
    return true;
}

void StartScene::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();
    btn->touchesMove(btn->BtnType::startBtn, touchLoc);
}

void StartScene::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();
    if (btn->touchesEnd(btn->BtnType::startBtn,touchLoc)) { // 進行場景的切換
        _bToGameScene = true;
    }
}