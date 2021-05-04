#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

class CCollider {
public:
	cocos2d::Point _colliderPos;
	cocos2d::Rect _range;

	void setBoxCollider(const cocos2d::Point pos, const cocos2d::Size size) {
		_colliderPos = pos;
		_range = Rect(_colliderPos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
	};
};

class CGameObject : public cocos2d::Node
{
public:
	CGameObject();
	~CGameObject();
	
	virtual void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder = 1);
	virtual void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& imgname, int zOrder = 1);

	virtual void update(float dt);

	virtual void setPosition(const cocos2d::Point pos);

	void initBoxCollider(const cocos2d::Point pos, const cocos2d::Size size);
	void setBoxCollider(const cocos2d::Point pos, const cocos2d::Size size);
	void setVisible(bool visible) {
		_objectNode->setVisible(visible);
	};

	bool OnColliderCheck(const CCollider& collider2);
	CCollider* getCollider();
	cocos2d::Point getPosition();
	
private:

protected:
	cocos2d::Point _position;
	CCollider* _collider;
	cocos2d::Sprite* _img;
	cocos2d::Node* _objectNode;
	cocos2d::Size _size;
};
