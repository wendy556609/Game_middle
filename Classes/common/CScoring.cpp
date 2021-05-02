#include "CScoring.h"

USING_NS_CC;

static CScoring* s_CScoring = nullptr;

CScoring::CScoring() {
    _score = 0;
    _scoreText = "Score : ";
    _scoreLabel = nullptr;
    isChange = false;
    _isGameStart = false;
    _isCountStart = false;
    _isInit = false;
    _moveSpeed = 150;
    _countTime = 0;
    _level = 1;
}

CScoring::~CScoring() {
    CC_SAFE_DELETE(s_CScoring);
}

CScoring* CScoring::create(cocos2d::Point scorePos, cocos2d::Point timePos, cocos2d::Node& parent, cocos2d::Size size, int zOrder) {
    if (!s_CScoring) {
        s_CScoring = new (std::nothrow)CScoring();
        s_CScoring->init(scorePos, timePos, parent, size, zOrder);
    }
    return s_CScoring;
}

CScoring* CScoring::getInstance() {
    if (!s_CScoring) {
        return nullptr;
    }
    return s_CScoring;
}

void CScoring::init(cocos2d::Point scorePos, cocos2d::Point timePos, cocos2d::Node& parent, cocos2d::Size size, int zOrder) {
    std::ostringstream ostr;
    ostr.str(""); // 設定字串為 null
    ostr  << _scoreText << _score;
    _scoreString = ostr.str();
    _scoreLabel = Label::createWithBMFont("fonts/couriernew32.fnt", _scoreString);

    _scoreLabel->setContentSize(size);
    _scoreLabel->setColor(Color3B::WHITE);
    _scoreLabel->setPosition(scorePos);

    ostr.str(""); // 設定字串為 null
    ostr << _countTime;
    _timeString = ostr.str();
    _timeLabel = Label::createWithBMFont("fonts/couriernew32.fnt", _timeString);
    _timeLabel->setColor(Color3B(209,73,63));
    _timeLabel->setPosition(timePos);
    _timeLabel->setBMFontSize(72);
    _timeLabel->setVisible(false);
    
    parent.addChild(_scoreLabel, zOrder);
    parent.addChild(_timeLabel, zOrder);
}

void CScoring::initState() {
    _score = 0;
    _level = 1;
    setScore(0);
    setMoveSpeed(2);
    setChange(false);
}

int CScoring::getScore(int score) {
    return _score;
}

void CScoring::setScore(int score) {
    _score += score;

    std::ostringstream ostr;
    ostr.str(""); // 設定字串為 null
    ostr << _scoreText << _score;
    _scoreString = ostr.str();
    _scoreLabel->setString(_scoreString);
    isChange = true;
}

void CScoring::setChange(bool change) {
    isChange = change;
}

bool CScoring::getChange() {
    return isChange;
}

void CScoring::setMoveSpeed(float speed) {
    _moveSpeed = 150 * speed;
}

float CScoring::getMoveSpeed() {
    return _moveSpeed;
}

void CScoring::setStart(bool start, int type) {
    if (type == 0) {
        _isCountStart = start;
    }
    else if(type == 1){
        _isGameStart = start;
    }
}
bool CScoring::getStart() {
    return _isGameStart;
}

void CScoring::update(float dt) {
    if (_isCountStart) {
        _timeLabel->setVisible(true);
        _countTime += dt;

        std::ostringstream ostr;
        ostr.str(""); // 設定字串為 null
        ostr << floorf(4-_countTime);
        _timeString = ostr.str();
        _timeLabel->setString(_timeString);
        if (_countTime >= 4) {
            _countTime = 0;
            _isCountStart = false;
            _isGameStart = true;
            _timeLabel->setVisible(false);
        }
    }
}