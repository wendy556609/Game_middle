#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CGameObject.h"

class CShadow : public CGameObject {
public:
	CShadow();
	~CShadow();
	void setTarget(cocos2d::Point target, cocos2d::Vec2 relativePos);

	cocos2d::Point _target;
	cocos2d::Vec2 _relativePos;
};

class CRunner : public CGameObject
{
private:
	
public:
	enum State{
		normal,
		happy,
		sad
	};
	CRunner();
	~CRunner();
	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder = 1);
	void setPosition(const cocos2d::Point pos);
	void changeFace();
	void setState(State state);
	void jumpAction(float dt);
	void update(float dt);

	State _state;
	CShadow* _shadow;
	cocostudio::timeline::ActionTimeline* _runAction;
	cocos2d::Point _initPos;
	cocos2d::Vec2 _cPos;
	bool _isJump;
	bool _hightPoint;

	bool _isHurt;
	float _jumptime;
	float _airTime;
};

