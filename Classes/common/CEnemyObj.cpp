#include "CEnemyObj.h"

CTriEnemy::CTriEnemy() {
	_startAnim = false;
	_showAction = nullptr;
	blood = 1;
	isEnable = false;
}
CTriEnemy::~CTriEnemy() {

}

void CTriEnemy::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder) {
	_position = position;
	_initPos = position;
	_objectNode = CSLoader::createNode(csbname);
	_size = _objectNode->getChildByName(layername)->getContentSize();
	initBoxCollider(position, _size);
	setPosition(position);
	parent.addChild(_objectNode, zOrder);

	_showAction = CSLoader::createTimeline(csbname);
	_objectNode->runAction(_showAction);
	
	initState();

	_moveSpeed = 150;
}

void CTriEnemy::initState() {
	setPosition(_initPos);

	int face = rand() % 2;
	int color = rand() % 3;

	changeFace(State(face));
	changeColor(color);
	_startAnim = false;
	_showAction->gotoFrameAndPause(0);
}

void CTriEnemy::changeColor(int type) {
	if (type == 0) {
		_objectNode->setColor(Color3B(40, 91, 143));
	}
	if (type == 1) {
		_objectNode->setColor(Color3B(180, 53, 44));
	}
	if (type == 2) {
		_objectNode->setColor(Color3B(134, 140, 43));
	}
}

void CTriEnemy::changeFace(State state) {
	_state = state;
	if (_state == State::happy) {
		_objectNode->getChildByName("triblock_1")->getChildByName("happyface")->setVisible(true);
		_objectNode->getChildByName("triblock_1")->getChildByName("sadface")->setVisible(false);
	}
	else if (_state == State::sad) {
		_objectNode->getChildByName("triblock_1")->getChildByName("happyface")->setVisible(false);
		_objectNode->getChildByName("triblock_1")->getChildByName("sadface")->setVisible(true);
	}
}

void CTriEnemy::update(float dt, Point move) {
	if (isEnable) {
		setPosition(Vec2(move.x, getPosition().y));
		if (getPosition().x >= 100 && !_startAnim) {
			_showAction->gotoFrameAndPlay(0, 35, false);
			_showAction->setTimeSpeed(1.0f);
			_startAnim = true;
		}
	}
}

CFEnemy::CFEnemy() {
	_showAction = nullptr;
	_startAnim = false;
	blood = 2;
}

CFEnemy::~CFEnemy() {

}

void CFEnemy::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder) {
	_position = position;
	_initPos = position;
	_objectNode = CSLoader::createNode(csbname);
	_size = _objectNode->getChildByName(layername)->getContentSize();
	_cPos = _objectNode->getChildByName(layername)->getPosition();
	initBoxCollider(position+ _cPos, _size);
	setPosition(position);
	parent.addChild(_objectNode, zOrder);

	_showAction = CSLoader::createTimeline(csbname);
	_objectNode->runAction(_showAction);

	initState();
}

void CFEnemy::setPosition(const cocos2d::Point pos) {
	_position = pos;
	_objectNode->setPosition(pos);
	setBoxCollider(pos + _cPos, _size);
}

void CFEnemy::initState() {
	setPosition(_initPos);

	_showAction->gotoFrameAndPause(0);
	_startAnim = false;
	repeatAnim = false;
}

void CFEnemy::update(float dt, Point move) {
	if (isEnable) {
		setPosition(Vec2(move.x, getPosition().y));
		if (getPosition().x >= 100 && !_startAnim) {
			_showAction->gotoFrameAndPlay(0, 30, false);
			_showAction->setTimeSpeed(1.0f);
			_startAnim = true;
			repeatAnim = true;
		}
		if (_showAction->getCurrentFrame() == 30 && repeatAnim) {
			_showAction->gotoFrameAndPlay(30, 60, true);
			repeatAnim = false;
		}
	}
}

CBEnemy::CBEnemy() {
	_showAction = nullptr;
	_startAnim = false;

	_isJump = false;
	_hightPoint = false;
	drop = false;
	_jumptime = 0;
	_waitTime = 0;
	blood = 3;
}

CBEnemy::~CBEnemy() {

}

void CBEnemy::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder) {
	_position = position;
	_objectNode = CSLoader::createNode(csbname);
	_size = _objectNode->getChildByName(layername)->getContentSize();
	_cPos = _objectNode->getChildByName(layername)->getPosition();
	_initPos = position + _cPos;
	initBoxCollider(position + _cPos, _size);
	setPosition(position);
	parent.addChild(_objectNode, zOrder);

	_showAction = CSLoader::createTimeline(csbname);
	_objectNode->runAction(_showAction);

	initState();
}

void CBEnemy::initState() {
	setPosition(_initPos);

	//_showAction->gotoFrameAndPlay(0, 18, false);
	_showAction->gotoFrameAndPause(0);
	_isJump = false;
	_hightPoint = false;
	drop = false;
	_jumptime = 0;
	_waitTime = 0;
	//_showAction->setTimeSpeed(1.0f);
	//_startAnim = false;
}

void CBEnemy::setPosition(const cocos2d::Point pos) {
	_position = pos;
	_objectNode->setPosition(pos);
	setBoxCollider(pos + _cPos, _size);
}

void CBEnemy::update(float dt, Point move) {
	if (isEnable) {
		Jump(dt, move);
	}
}

void CBEnemy::Jump(float dt, Point move) {
	Point pos;
	if (_isJump) {
		if (!_hightPoint) {
			_jumptime += dt;
			float ph = sinf(_jumptime * M_PI / 1.0f);
			pos = Vec2(move.x, _initPos.y + ph * 300);
			if (_jumptime >= 0.5f&& !drop) {
				pos = Vec2(move.x, _initPos.y + 300);
				_hightPoint = true;
			}
			setPosition(pos);
		}
		else {
			_waitTime += dt;
			pos = Vec2(move.x, _initPos.y + 300);
			if (_waitTime > 0.5f) {
				_waitTime = 0;
				_hightPoint = false;
				drop = true;
				_showAction->gotoFrameAndPlay(18, 30, false);
				_showAction->setTimeSpeed(1.0f);
			}
			setPosition(pos);
		}
		if (_jumptime > 1.0f) {
			_jumptime = 0;
			pos = Vec2(move.x, _initPos.y);
			setPosition(pos);
			//setPosition(Vec2(move.x, _initPos.y));
			_waitTime = 0;
			_hightPoint = false;
			_isJump = false;
		}
	}
	else {
		_waitTime += dt;
		pos = Vec2(move.x, _initPos.y);
		_showAction->gotoFrameAndPause(0);
		if (_waitTime > 0.5f) {
			_waitTime = 0;
			_isJump = true;
			drop = false;
			_showAction->gotoFrameAndPlay(0, 18, false);
			_showAction->setTimeSpeed(1.0f);
		}
		setPosition(pos);
	}
	
	
	
}

