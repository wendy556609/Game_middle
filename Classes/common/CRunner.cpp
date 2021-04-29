#include "CRunner.h"

USING_NS_CC;

CRunner::CRunner()
{
	_isJump = false;
	_shadow = nullptr;
	_runAction = nullptr;
	_hightPoint = false;
	_jumptime = 0;
	_isHurt = false;
}

CRunner::~CRunner()
{
	CC_SAFE_DELETE(_shadow);
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
	_runAction->gotoFrameAndPlay(0, 24, true);
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

void CRunner::changeFace() {
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
	
	if (_isJump) {
		_jumptime += dt;
		float ph = sinf(_jumptime * M_PI/1.0f);
		Point pos = Vec2(getPosition().x, _initPos.y + ph*250 );
		setPosition(pos);
		_runAction->setTimeSpeed(0.5f);
		if (_jumptime > 1.0f) {
			_jumptime = 0;
			setPosition(Vec2(getPosition().x, _initPos.y));
			_isJump = false;
			_runAction->setTimeSpeed(1.0f);
		}
	}
}

void CRunner::update(float dt) {
	jumpAction(dt);
}

void CRunner::setState(State state) {
	_state = state;
}


CShadow::CShadow()
{
}

CShadow::~CShadow()
{
}

void CShadow::setTarget(cocos2d::Point target, cocos2d::Vec2 relativePos) {
	_target = target;
	_relativePos = relativePos;
	setPosition(target + _relativePos);
}