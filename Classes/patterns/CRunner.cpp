#include "CRunner.h"

USING_NS_CC;

CRunner::CRunner()
{
	_blood = TOTBLOOD;
	
	_shadow = nullptr;
	_runAction = nullptr;

	_isJump = false;
	_hightPoint = false;
	_isHurt = false;
	drop = false;
	isChange = false;
	passing = false;
	_isStart = false;

	_airTime = 0;
	_faceTime = 0;
	_jumptime = 0;
}

CRunner::~CRunner()
{
	CC_SAFE_DELETE(_shadow);
}

void CRunner::initState() {
	_blood = TOTBLOOD;

	setPosition(_initPos);

	_objectNode->setColor(Color3B::WHITE);
	_runAction->gotoFrameAndPause(0);
	_runAction->setTimeSpeed(1.0f);
	changeFace(State::normal);
	
	_isJump = false;
	_hightPoint = false;
	_isHurt = false;
	drop = false;
	isChange = false;
	passing = false;
	_isStart = false;

	_jumptime = 0;
	_airTime = 0;
	_faceTime = 0;
}

void CRunner::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder) {
	_position = position;
	_initPos = position;
	_objectNode = CSLoader::createNode(csbname);
	_size = _objectNode->getChildByName(layername)->getContentSize();
	_cPos = _objectNode->getChildByName(layername)->getPosition();
	initBoxCollider(position+ _cPos, _size);
	
	_shadow = new (std::nothrow) CShadow();
	_shadow->init(_position, parent, "cubershadow",2);
	_shadow->setTarget(_position, Vec2(0, -_objectNode->getChildByName("body_cuber1")->getContentSize().height / 2));

	setPosition(position);

	parent.addChild(_objectNode, zOrder);

	_runAction= CSLoader::createTimeline(csbname);
	_runAction->gotoFrameAndPause(0);
	_runAction->setTimeSpeed(1.0f);
	_objectNode->runAction(_runAction);
	_state = State::normal;
}

void CRunner::setPosition(const cocos2d::Point pos) {
	_position = pos;
	_objectNode->setPosition(pos);
	_shadow->setPosition(Vec2(_position.x, _shadow->getPosition().y));
	setBoxCollider(pos+_cPos, _size);
}

void CRunner::changeFace(State face) {
	setState(face);
	if (_state == State::normal) {
		_objectNode->getChildByName("neutal_face")->setVisible(true);
		_objectNode->getChildByName("happy_face")->setVisible(false);
		_objectNode->getChildByName("sadness_face")->setVisible(false);
	}
	else if (_state == State::happy) {
		_objectNode->getChildByName("neutal_face")->setVisible(false);
		_objectNode->getChildByName("happy_face")->setVisible(true);
		_objectNode->getChildByName("sadness_face")->setVisible(false);
	}
	else if (_state == State::sad) {
		_objectNode->getChildByName("neutal_face")->setVisible(false);
		_objectNode->getChildByName("happy_face")->setVisible(false);
		_objectNode->getChildByName("sadness_face")->setVisible(true);
	}
}
void CRunner::jumpAction(float dt) {
	Point pos;
	if (_isJump) {
		if (!_hightPoint) {
			_jumptime += dt;
			float ph = sinf(_jumptime * M_PI / 1.0f);
			pos = Vec2(getPosition().x, _initPos.y + ph * 300);
			if (_jumptime >= 0.5f && !drop) {
				_hightPoint = true;
				drop = true;
			}
		}
		else {
			_airTime += dt;
			pos = Vec2(getPosition().x, _initPos.y + 300);
			if (_airTime > 0.5f) {
				_airTime = 0;
				_hightPoint = false;
			}
		}
		setPosition(pos);
		_runAction->setTimeSpeed(0.5f);
		if (_jumptime > 1.0f) {
			_jumptime = 0;
			setPosition(Vec2(getPosition().x, _initPos.y));
			_isJump = false;
			_runAction->setTimeSpeed(1.0f);
			_airTime = 0;
			_hightPoint = false;
			drop = false;
			isChange = true;
		}
	}
}

void CRunner::update(float dt) {
	if (!_isStart) {
		_isStart = true;
		_runAction->gotoFrameAndPlay(0, 24, true);
	}
	jumpAction(dt);
	hurtAct(dt);
}

void CRunner::setState(State state) {
	_state = state;
}

void CRunner::hurtAct(float dt) {
	if (_isHurt) {
		if (_faceTime == 0) {
			CScoring::getInstance()->setMoveSpeed(1.5f);
			CScoring::getInstance()->setChange(true);
		}
		_faceTime += dt;

		changeFace(State::sad);
		_objectNode->setColor(Color3B(82, 131, 151));
		_runAction->setTimeSpeed(0.75f);

		isChange = true;
		passing = false;
		if (_faceTime >= 1.5f) {
			_faceTime = 0;
			isChange = false;
			_isHurt = false;
			CScoring::getInstance()->setChange(false);

			changeFace(State::normal);
			_objectNode->setColor(Color3B(255, 255, 255));
			CScoring::getInstance()->setMoveSpeed(2.0f);
			_runAction->setTimeSpeed(1.0f);
		}
	}
	else if (passing) {
		if (isChange) {
			if (_faceTime == 0) {
				CScoring::getInstance()->setScore(CScoring::getInstance()->currentScore);
				CScoring::getInstance()->setMoveSpeed(3.0f);
				CScoring::getInstance()->setChange(true);
			}
			_faceTime += dt;

			changeFace(State::happy);
			_objectNode->setColor(Color3B(247, 151, 149));
			_runAction->setTimeSpeed(1.25f);
			if (_faceTime >= 1.0f) {
				_faceTime = 0;
				isChange = false;
				passing = false;
				CScoring::getInstance()->setChange(false);

				changeFace(State::normal);
				_objectNode->setColor(Color3B(255, 255, 255));
				CScoring::getInstance()->setMoveSpeed(2.0f);
				_runAction->setTimeSpeed(1.0f);
			}
		}
	}
	else {
		isChange = false;
	}
}

void CRunner::getHurt(int blood) {
	_blood -= blood;
	if (_blood <= 0) {
		_blood = 0;
	}
}