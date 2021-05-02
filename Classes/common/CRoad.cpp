#include "CRoad.h"

USING_NS_CC;

#define X_OFFSET  100
#define SHIFTX(X) ((rand()%(2*(X)))- (X))

CRoad::CRoad() {
	genLoc[0] = Point(240, 124); genLoc[1] = Point(640, 124); genLoc[2] = Point(1040, 124);
	_road = nullptr;
	_roadobj[0] = _roadobj[1] = _roadobj[2] = nullptr;
	_iroadon[0] = _iroadon[1] = _iroadon[2] = 1;

	movespeed = 1;
}

CRoad::~CRoad() {

}

void CRoad::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& imgname) {
	std::string objname;
	_road = Sprite::createWithSpriteFrameName(imgname + ".png");
	_initPos = position;
	_road->setPosition(_initPos);
	parent.addChild(_road, 1); // 高於背景層

	_roadobj[0] = CSLoader::createNode("./patterns/midobj.csb");
	_roadobj[1] = CSLoader::createNode("./patterns/midobj.csb");
	_roadobj[2] = CSLoader::createNode("./patterns/midobj.csb");

	for (int i = 1; i <= 6; i++)
	{
		std::ostringstream ostr;
		ostr << "mid0" << i;
		objname = ostr.str();
		_roadobj[0]->getChildByName(objname)->setVisible(false);
		_roadobj[1]->getChildByName(objname)->setVisible(false);
		_roadobj[2]->getChildByName(objname)->setVisible(false);
	}
	_road->addChild(_roadobj[0], -1); _roadobj[0]->setPosition(genLoc[0] + Point(SHIFTX(X_OFFSET), 0));
	_road->addChild(_roadobj[1], -1); _roadobj[1]->setPosition(genLoc[1] + Point(SHIFTX(X_OFFSET), 0));
	_road->addChild(_roadobj[2], -1); _roadobj[2]->setPosition(genLoc[2] + Point(SHIFTX(X_OFFSET), 0));
	resetObj();
}

void CRoad::update(float dt)  // 根據時間自己移動
{
	//目前的移動設定移動的距離
	Point pt = _road->getPosition();
	pt.x += dt * movespeed;
	if (pt.x >= 1920) {
		pt.x = -2 * 1280 + pt.x;
		resetObj();
	}
	_road->setPosition(pt);
}

void CRoad::resetObj() {
	std::ostringstream ostr;
	std::string objname;

	//clear
	ostr.str(""); ostr.clear();
	ostr << "mid0" << _iroadon[0]; objname = ostr.str();
	_roadobj[0]->getChildByName(objname)->setVisible(false);

	ostr.str(""); ostr.clear();
	ostr << "mid0" << _iroadon[1]; objname = ostr.str();
	_roadobj[1]->getChildByName(objname)->setVisible(false);

	ostr.str(""); ostr.clear();
	ostr << "mid0" << _iroadon[2]; objname = ostr.str();
	_roadobj[2]->getChildByName(objname)->setVisible(false);
	//add
	_iroadon[0] = rand() % 6 + 1;
	ostr.str(""); ostr.clear();
	ostr << "mid0" << _iroadon[0]; objname = ostr.str();
	_roadobj[0]->getChildByName(objname)->setVisible(true);

	_iroadon[1] = rand() % 6 + 1;
	while (_iroadon[1] == _iroadon[0])
	{
		_iroadon[1] = rand() % 6 + 1;
	}
	ostr.str(""); ostr.clear();
	ostr << "mid0" << _iroadon[1]; objname = ostr.str();
	_roadobj[1]->getChildByName(objname)->setVisible(true);

	_iroadon[2] = rand() % 6 + 1;
	while (_iroadon[2] == _iroadon[0] || _iroadon[2] == _iroadon[1])
	{
		_iroadon[2] = rand() % 6 + 1;
	}
	ostr.str(""); ostr.clear();
	ostr << "mid0" << _iroadon[2]; objname = ostr.str();
	_roadobj[2]->getChildByName(objname)->setVisible(true);
}

void CRoad::setSpeed(float speed) {
	movespeed = speed;
}

void CRoad::initState() {
	resetObj();
	_road->setPosition(_initPos);
}