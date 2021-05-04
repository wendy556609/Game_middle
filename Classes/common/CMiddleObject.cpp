#include "CMiddleObject.h"

USING_NS_CC;

CMiddleObject::CMiddleObject(){
	_road0 = nullptr;
	_road1 = nullptr;
}

CMiddleObject::~CMiddleObject() {
	CC_SAFE_DELETE(_road0);
	CC_SAFE_DELETE(_road1);
}

void CMiddleObject::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& imgname) {
	_road0 = new (std::nothrow)CRoad();
	_road0->init(position, parent, imgname);

	_road1 = new (std::nothrow)CRoad();
	_road1->init(position - Point(1280, 0), parent, imgname);
}

void CMiddleObject::update(float dt)  // 根據時間自己移動
{
	_road0->update(dt);
	_road1->update(dt);
}

void CMiddleObject::setSpeed(float speed) {
	_road0->setSpeed(speed);
	_road1->setSpeed(speed);
}

void CMiddleObject::initState() {
	_road0->initState();
	_road1->initState();
}