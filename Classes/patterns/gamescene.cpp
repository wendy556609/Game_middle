#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene() {
    _c3sButton = nullptr;
    _midObj = nullptr;
    _runner = nullptr;
    _enemy = nullptr;
    _Bar = nullptr;
}

GameScene::~GameScene() {
    CC_SAFE_DELETE(_c3sButton);
    CC_SAFE_DELETE(_midObj);
    CC_SAFE_DELETE(_runner);
    CC_SAFE_DELETE(_enemy);
    CC_SAFE_DELETE(_Bar);
    this->removeAllChildren();

    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gamescene.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gamescene_object.plist");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();

    SimpleAudioEngine::getInstance()->end();

    AudioEngine::end();
}

Scene* GameScene::createScene()
{
    return GameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init() {
    if (!Scene::init()) { return false; }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 設定搜尋路徑
    std::vector<std::string> searchPath;
    searchPath.push_back("./patterns/");
    CCFileUtils::getInstance()->setSearchPaths(searchPath);

    auto rootNode = CSLoader::createNode("mainscene.csb");
    this->addChild(rootNode); // 加入目前的 scene 中

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gamescene.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gamescene_object.plist");

    auto loctag = dynamic_cast<cocos2d::Node*>(rootNode->getChildByName("_runner"));
    loctag->setVisible(false);
    auto position = loctag->getPosition();
    _runner = new (std::nothrow) CRunner();
    _runner->init(position, *this, "runner_demo.csb", "collider", 3);

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

    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("startButton"));
    loctag->setVisible(false);
    position = loctag->getPosition();
    _c3sButton->init(_c3sButton->BtnType::startBtn, position, *this, "startnormal", "starton");

    CScoring::create()->init(1, position, *this);

    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("replaybtn"));
    loctag->setVisible(false);
    position = loctag->getPosition();
    _c3sButton->init(_c3sButton->BtnType::restartBtn, position, *this, "replaybtn", "replaybtn");

    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("speedButton"));
    loctag->setVisible(false);
    position = loctag->getPosition();
    _c3sButton->init(_c3sButton->BtnType::runBtn, position, *this, "runnormal", "runon");

    loctag = dynamic_cast<cocos2d::Sprite*>(rootNode->getChildByName("btn_cuber"));
    loctag->setVisible(false);
    position = loctag->getPosition();
    _c3sButton->init(_c3sButton->BtnType::boardBtn, position, *this, "cuberbtn1", "cuberbtn2");

    _enemy = new (std::nothrow)CEnemy();
    _enemy->init(*this, _runner->getPosition());

    loctag = dynamic_cast<cocos2d::Node*>(rootNode->getChildByName("scoreText"));
    loctag->setVisible(false);
    position = loctag->getPosition();

    CScoring::getInstance()->init(0, position, *this);

    loctag = dynamic_cast<cocos2d::Node*>(rootNode->getChildByName("LevelText"));
    loctag->setVisible(false);
    position = loctag->getPosition();

    CScoring::getInstance()->init(2, position, *this);

    loctag = dynamic_cast<cocos2d::Node*>(rootNode->getChildByName("bloodBar_track"));
    loctag->setVisible(false);
    position = loctag->getPosition();

    _Bar = new (std::nothrow)CCanvas();
    _Bar->init(1, position, *this);

    loctag = dynamic_cast<cocos2d::Node*>(rootNode->getChildByName("gameSlider_track"));
    loctag->setVisible(false);
    position = loctag->getPosition();

    _Bar->init(2, position, *this);

    //創建一個一對一的事件聆聽器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);//加入觸碰移動事件
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);//加入觸碰離開事件

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);	//加入剛創建的事件聆聽器
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::update));

    return true;
}

void GameScene::update(float dt) {
    if (CScoring::getInstance()->getStart()) {
        if (!CScoring::getInstance()->_isFinal) {
            if (CScoring::getInstance()->_isInit) {
                CScoring::getInstance()->_isInit = false;
                _c3sButton->setEnable(true);
                _c3sButton->setEnable(false, _c3sButton->BtnType::boardBtn);
            }

            _midObj->update(dt);
            _runner->update(dt);
            _enemy->update(dt);

            _c3sButton->setEnable(!_runner->_isJump, _c3sButton->BtnType::jumpBtn);

            if (_runner->_isJump) {
                if (!_runner->passing) {
                    _runner->passing = _enemy->passPlayer(*_runner);
                    CScoring::getInstance()->currentScore = _enemy->getPassScore();
                }
            }

            _enemy->setSpeed(CScoring::getInstance()->getMoveSpeed());
            _midObj->setSpeed(CScoring::getInstance()->getMoveSpeed());

            if (_enemy->checkCollider(*_runner)) {
                if (!_runner->_isHurt) {
                    _runner->_faceTime = 0;
                    _runner->getHurt(_enemy->getHurt());
                    _runner->_isHurt = true;
                    _Bar->setBlood(_runner->_blood);
                }
            }

            _Bar->update();
        }
    }
    else {
        if (!CScoring::getInstance()->_isInit) {
            CScoring::getInstance()->initState();
            _runner->initState();
            _enemy->initState();
            _midObj->initState();
            _c3sButton->initState();
            _Bar->initState();

            _c3sButton->setEnable(true, _c3sButton->BtnType::boardBtn);
            CScoring::getInstance()->_isInit = true;
        }
    }

    CScoring::getInstance()->update(dt);
}

bool GameScene::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();

    if (_c3sButton->touchesBegin(touchLoc, _c3sButton->BtnType::jumpBtn)) {
        _runner->_isJump = true;
        CScoring::getInstance()->setPlay(0, true);
    }
    _c3sButton->touchesBegin(touchLoc);

    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();

    _c3sButton->touchesMove(touchLoc);
}

void GameScene::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();

    _c3sButton->touchesEnd(touchLoc);
}