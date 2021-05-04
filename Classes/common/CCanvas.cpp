#include"CCanvas.h"

USING_NS_CC;

CBar::CBar() {
	_barBase = nullptr;
	_barSprite = nullptr;
}

CBar::~CBar() {

}

void CBar::initState() {
	_currentValue = _initValue;

	setBar(_currentValue);
}

void CBar::init(cocos2d::Point pos, cocos2d::Node& parent, float initValue,cocos2d::Vec2 size, int zOrder) {
	_barBase = Sprite::createWithSpriteFrameName("sliderTrack.png");
	_barSprite = Sprite::createWithSpriteFrameName("sliderProgress.png");

	_initPos = pos;
	_movePos = _initPos;
	_barBase->setPosition(pos);
	_barSprite->setPosition(pos);

	parent.addChild(_barBase, zOrder);
	parent.addChild(_barSprite, zOrder);

	_barSprite->setContentSize(Size(_barSprite->getContentSize().width* size.x, _barSprite->getContentSize().height*size.y));
	_barBase->setContentSize(_barSprite->getContentSize());
	_initSize = _barSprite->getContentSize();
	_barSize = _initSize;

	_initValue = initValue;
	_currentValue = _initValue;
}

void CBar::setBar(int value) {
	_currentValue = value;

	_barSize.width = _initSize.width * (_currentValue / _initValue);
	_barSprite->setContentSize(_barSize);

	_movePos.x = _initPos.x - (_initSize.width - _barSize.width) / 2;
	_barSprite->setPosition(_movePos);
}

CTimeBar::CTimeBar() {
	_timeBarIcon = nullptr;
}

void CTimeBar::initTimeState() {
	initState();

	setTimeBar(_initValue);
}

void CTimeBar::initAll(cocos2d::Point pos, cocos2d::Node& parent, float initValue, cocos2d::Vec2 size, int zOrder) {
	init(pos, parent, initValue, size, zOrder);

	_timeBarIcon= Sprite::createWithSpriteFrameName("cuberslider.png");
	parent.addChild(_timeBarIcon, zOrder);

	setTimeBar(initValue);
}

void CTimeBar::setTimeBar(int value) {
	if (value <= 0) {
		setBar(0);
	}
	else {
		setBar(value);
	}

	_timeBarIcon->setPosition(Vec2(_movePos.x + _barSize.width / 2, _movePos.y));
}

CCanvas::CCanvas() {
	_bloodBar = nullptr;
	_timeBar = nullptr;
	_bloodLabel = nullptr;
}

CCanvas::~CCanvas() {
	CC_SAFE_DELETE(_bloodBar);
	CC_SAFE_DELETE(_timeBar);
}

void CCanvas::initState() {
	_bloodBar->initState();
	_timeBar->initTimeState();

	std::ostringstream ostr;
	ostr.str(""); // 設定字串為 null
	ostr << TOTBLOOD;
	_bloodString = ostr.str();

	_bloodLabel->setString(_bloodString);
}

void CCanvas::init(int type, cocos2d::Point pos, cocos2d::Node& parent, int zOrder) {
	if (type == 1) {
		_bloodBar = new (std::nothrow)CBar();
		_bloodBar->init(pos, parent, TOTBLOOD,Vec2(0.8,1), zOrder);

		std::ostringstream ostr;
		ostr.str(""); // 設定字串為 null
		ostr << TOTBLOOD;
		_bloodString = ostr.str();
		_bloodLabel = Label::createWithBMFont("fonts/couriernew32.fnt", _bloodString);

		_bloodLabel->setBMFontSize(24);
		_bloodLabel->setColor(Color3B::WHITE);
		_bloodLabel->setPosition(Vec2((pos.x - _bloodBar->_barBase->getContentSize().width * 0.6f), pos.y));

		parent.addChild(_bloodLabel, zOrder);
		
	}
	else if(type == 2) {
		_timeBar = new (std::nothrow)CTimeBar();
		_timeBar->initAll(pos, parent, FINALTIME, Vec2(1.25, 1.25), zOrder);
	}
}

void CCanvas::setBlood(int blood) {
	_bloodBar->setBar(blood);

	std::ostringstream ostr;
	ostr.str(""); // 設定字串為 null
	ostr << _bloodBar->_currentValue;
	_bloodString = ostr.str();

	_bloodLabel->setString(_bloodString);

	if (_bloodBar->_currentValue == 0) {
		CScoring::getInstance()->_isFinal=true;
		CScoring::getInstance()->_isGameOver = true;
	}
}

void CCanvas::update() {
	_timeBar->setTimeBar(CScoring::getInstance()->getTime());
}