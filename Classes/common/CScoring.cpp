#include "CScoring.h"

USING_NS_CC;

CScoreBoard::CScoreBoard() {
    _board = nullptr;
    _medals[0] = _medals[1] = _medals[2] = nullptr;
    _bestScore[0] = _bestScore[1] = _bestScore[2] = 0;
}

CScoreBoard::~CScoreBoard() {

}

void CScoreBoard::init(cocos2d::Node& parent, int zOrder) {
    _board= Sprite::createWithSpriteFrameName("ranking.png");
    _board->setPosition(Vec2(640, 360));
    parent.addChild(_board, zOrder);

    std::string text;
    std::ostringstream ostr;

    ostr.str(""); // 設定字串為 null
    ostr << "Score : " << _bestScore[0];
    text = ostr.str();
    _medals[0] = Label::createWithBMFont("fonts/couriernew32.fnt", text);
    _medals[0]->setBMFontSize(48);
    _medals[0]->setColor(Color3B::WHITE);
    _medals[0]->setPosition(Vec2(500,360));

    ostr.str(""); // 設定字串為 null
    ostr << "Score : " << _bestScore[1];
    text = ostr.str();
    _medals[1] = Label::createWithBMFont("fonts/couriernew32.fnt", text);
    _medals[1]->setBMFontSize(48);
    _medals[1]->setColor(Color3B::WHITE);
    _medals[1]->setPosition(Vec2(500, 220));

    ostr.str(""); // 設定字串為 null
    ostr << "Score : " << _bestScore[2];
    text = ostr.str();
    _medals[2] = Label::createWithBMFont("fonts/couriernew32.fnt", text);
    _medals[2]->setBMFontSize(48);
    _medals[2]->setColor(Color3B::WHITE);
    _medals[2]->setPosition(Vec2(500, 85));

    _board->addChild(_medals[0], zOrder);
    _board->addChild(_medals[1], zOrder);
    _board->addChild(_medals[2], zOrder);

    setVisible(false);
}

void CScoreBoard::setVisible(bool visible) {
    _board->setVisible(visible);
}

void CScoreBoard::checkBestScore(int score) {
    if (score > _bestScore[0]) {
        int m1, m2;
        m1 = _bestScore[0]; m2 = _bestScore[1];
        _bestScore[0] = score;
        _bestScore[1] = m1;
        _bestScore[2] = m2;
        setString();
    }
    else if (score > _bestScore[1]) {
        int m1, m2;
        m1 = _bestScore[0]; m2 = _bestScore[1];
        _bestScore[0] = m1;
        _bestScore[1] = score;
        _bestScore[2] = m2;
        setString();
    }
    else if (score > _bestScore[2]) {
        _bestScore[2] = score;
        setString();
    }
}

void CScoreBoard::setString() {
    std::string text;
    std::ostringstream ostr;

    ostr.str(""); // 設定字串為 null
    ostr << "Score : " << _bestScore[0];
    text = ostr.str();
    _medals[0]->setString(text);

    ostr.str(""); // 設定字串為 null
    ostr << "Score : " << _bestScore[1];
    text = ostr.str();
    _medals[1]->setString(text);

    ostr.str(""); // 設定字串為 null
    ostr << "Score : " << _bestScore[2];
    text = ostr.str();
    _medals[2]->setString(text);
}

static CScoring* s_CScoring = nullptr;

CScoring::CScoring() {
    _score = 0;
    _scoreText = "Score : ";
    _levelText = "Level ";
    _scoreLabel = nullptr;
    _timeLabel = nullptr;
    _levelLabel = nullptr;
    _scoreBoard = nullptr;
    _endLabel = nullptr;

    isChange = false;
    _isGameStart = false;
    _isCountStart = false;
    _isFinal = false;
    _isInit = false;
    _isGameOver = false;
    _moveSpeed = 150;
    _countTime = 0;
    _finalTime = 60;
    _currentTime = 10;
    _level = 1;
}

CScoring::~CScoring() {
    CC_SAFE_DELETE(_scoreBoard);
    CC_SAFE_DELETE(s_CScoring);
}

CScoring* CScoring::create() {
    if (!s_CScoring) {
        s_CScoring = new (std::nothrow)CScoring();
    }
    return s_CScoring;
}

CScoring* CScoring::getInstance() {
    if (!s_CScoring) {
        return nullptr;
    }
    return s_CScoring;
}

//0_score 1_time 2_level
void CScoring::init(int type, cocos2d::Point pos, cocos2d::Node& parent, int zOrder) {
    std::ostringstream ostr;
    ostr.str(""); // 設定字串為 null
    if (type == 0) {
        ostr << _scoreText << _score;
        _scoreString = ostr.str();
        _scoreLabel = Label::createWithBMFont("fonts/couriernew32.fnt", _scoreString);

        _scoreLabel->setBMFontSize(36);
        _scoreLabel->setColor(Color3B::WHITE);
        _scoreLabel->setPosition(pos);

        parent.addChild(_scoreLabel, zOrder);

        _scoreBoard = new (std::nothrow)CScoreBoard();
        _scoreBoard->init(parent, zOrder + 1);

    }
    else if (type == 1) {
        ostr << _countTime;
        _timeString = ostr.str();
        _timeLabel = Label::createWithBMFont("fonts/couriernew32.fnt", _timeString);
        _timeLabel->setColor(Color3B(209, 73, 63));
        _timeLabel->setPosition(pos);
        _timeLabel->setBMFontSize(72);
        _timeLabel->setVisible(false);

        parent.addChild(_timeLabel, zOrder);

        ostr.str(""); // 設定字串為 null
        ostr << "Time's up";
        _endString = ostr.str();
        _endLabel = Label::createWithBMFont("fonts/couriernew32.fnt", _endString);
        _endLabel->setColor(Color3B(209, 73, 63));
        _endLabel->setPosition(pos);
        _endLabel->setBMFontSize(72);
        _endLabel->setVisible(false);

        parent.addChild(_endLabel, zOrder);
    }
    else if (type == 2) {
        ostr << _levelText <<_level;
        _levelString = ostr.str();
        _levelLabel = Label::createWithBMFont("fonts/couriernew32.fnt", _levelString);
        _levelLabel->setColor(Color3B::WHITE);
        _levelLabel->setBMFontSize(24);
        _levelLabel->setPosition(pos);

        parent.addChild(_levelLabel, zOrder);
    }
}

void CScoring::initState() {
    currentScore = 0;
    _score = 0;
    _level = 1;
    _currentTime = _finalTime;
    _isFinal = false;
    setScore(0);
    setMoveSpeed(2);
    setChange(false);
}

int CScoring::getScore() {
    return _score;
}

void CScoring::setScore(int score) {
    _score += score;

    std::ostringstream ostr;
    ostr.str(""); // 設定字串為 null
    ostr << _scoreText << _score;
    _scoreString = ostr.str();
    _scoreLabel->setString(_scoreString);

    setLevel();
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
int CScoring::getLevel(){ return _level; }

void CScoring::update(float dt) {
    if (_isCountStart) {
        _timeLabel->setVisible(true);
        _countTime += dt;

        std::ostringstream ostr;
        ostr.str(""); // 設定字串為 null
        
        if (floorf(4 - _countTime) == 0) {
            ostr << "GO";
        }
        else {
            ostr << floorf(4 - _countTime);
        }

        _timeString = ostr.str();
        _timeLabel->setString(_timeString);
        _timeLabel->enableShadow();
        if (_countTime >= 4) {
            _countTime = 0;
            _isCountStart = false;
            _isGameStart = true;
            _timeLabel->setVisible(false);
        }
    }
    else if (_isGameStart) {
        setTime(dt);
        setGameOver(dt);
    }
}

void CScoring::setLevel() {
    std::ostringstream ostr;
    ostr.str(""); // 設定字串為 null

    if (_score >= 10) {
        _level = 3;
    }
    else if (_score >= 5) {
        _level = 2;
    }
    else _level = 1;

    ostr << _levelText << _level;
    _levelString = ostr.str();
    _levelLabel->setString(_levelString);
}

void CScoring::setTime(float time) {
    _currentTime -= time;
    
    if (_currentTime <= 0) {
        _currentTime = _finalTime;
        _isFinal = true;
        _isGameOver = false;
    }
}

void CScoring::setGameOver(float time) {
    if (_isFinal) {
        if (_isGameOver) {
            std::ostringstream ostr;
            ostr.str(""); // 設定字串為 null
            std::string text;

            _countTime += time;

            ostr << "Game Over";
            text = ostr.str();
            _endLabel->setString(text);

            _endLabel->setVisible(true);

            if (_countTime >= 3) {
                _isFinal = false;
                _countTime = 0;
                _endLabel->setVisible(false);
                _isGameStart = false;
            }
        }
        else {
            std::ostringstream ostr;
            ostr.str(""); // 設定字串為 null
            std::string text;

            _countTime += time;

            ostr << "Time's Up";
            text = ostr.str();
            _endLabel->setString(text);

            _endLabel->setVisible(true);
            if (_countTime >= 3) {
                _isFinal = false;
                _countTime = 0;
                _endLabel->setVisible(false);
                _scoreBoard->checkBestScore(_score);
                _isGameStart = false;
            }
        }
    }
}

float CScoring::getTime() {
    return _currentTime;
}

void CScoring::setBoardVisible(bool visible) {
    _scoreBoard->setVisible(visible);
}