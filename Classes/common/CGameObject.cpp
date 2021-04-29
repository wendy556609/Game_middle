#include "CGameObject.h"

CGameObject::CGameObject()
{
	_collider = nullptr;
	_img = nullptr;
	_objectNode = nullptr;
}

CGameObject::~CGameObject()
{
	CC_SAFE_DELETE(_collider);
}

void CGameObject::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder) {
	_position = position;
	_objectNode = CSLoader::createNode(csbname);
	_size = _objectNode->getChildByName(layername)->getContentSize();
	_objectNode->getChildByName(layername)->setPosition(position);
	initBoxCollider(position, _size);
	setPosition(position);
	parent.addChild(_objectNode, zOrder);
}

void  CGameObject::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& imgname, int zOrder) {
	_position = position;
	_img = Sprite::createWithSpriteFrameName(imgname+".png");
	_size =	_img->getContentSize();
	initBoxCollider(position, _size);
	setPosition(position);
	parent.addChild(_img, zOrder);
}

void CGameObject::update(float dt) {

}

void CGameObject::setPosition(const cocos2d::Point pos){
	_position = pos;
	if (_img != nullptr) {
		_img->setPosition(pos);
	}
	else if (_objectNode != nullptr) {
		_objectNode->setPosition(pos);
	}
	setBoxCollider(pos, _size);
}

void CGameObject::initBoxCollider(const cocos2d::Point pos, const cocos2d::Size size) {
	if (!_collider)
	{
		_collider = new(std::nothrow)CCollider();
	}
	_collider->setBoxCollider(pos, size);
}

void CGameObject::setBoxCollider(const cocos2d::Point pos, const cocos2d::Size size) {
	_collider->setBoxCollider(pos, size);
}

bool CGameObject::OnColliderCheck(const CCollider& collider2) {
	cocos2d::Point lefttop_2 =Vec2(collider2._colliderPos.x- collider2._range.size.width/2, collider2._colliderPos.y + collider2._range.size.height / 2);
	cocos2d::Point rightbottom_2 = Vec2(collider2._colliderPos.x + collider2._range.size.width / 2, collider2._colliderPos.y - collider2._range.size.height / 2);
	cocos2d::Point leftbottom_2 = Vec2(collider2._colliderPos.x - collider2._range.size.width / 2, collider2._colliderPos.y - collider2._range.size.height / 2);
	cocos2d::Point righttop_2 = Vec2(collider2._colliderPos.x + collider2._range.size.width / 2, collider2._colliderPos.y + collider2._range.size.height / 2);

	if (_collider->_range.containsPoint(lefttop_2)|| _collider->_range.containsPoint(rightbottom_2)|| _collider->_range.containsPoint(leftbottom_2)|| _collider->_range.containsPoint(righttop_2)) {
		return true;
	}
	return false;
}

CCollider* CGameObject::getCollider() {
	return _collider;
}

cocos2d::Point CGameObject::getPosition() {
	return _position;
}
