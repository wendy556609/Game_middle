#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CGameObject.h"

USING_NS_CC;

class CEnemyObj : public CGameObject {
private:

public:
	CEnemyObj() {};
	~CEnemyObj() {};
	virtual void initState()=0;
	virtual void update(float dt, Point move)=0;
	void setEnable(bool enable) {
		isEnable = enable;
	}

	cocostudio::timeline::ActionTimeline* _showAction;
	cocos2d::Point _initPos;
	cocos2d::Vec2 _cPos;
	float _posY;
	float _moveSpeed;
	int blood;
	bool _startAnim;
	bool isEnable;
};

class CTriEnemy : public CEnemyObj {
private:

public:
	enum State {
		happy,
		sad
	};
	CTriEnemy();
	~CTriEnemy();
	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder = 1);
	void initState();
	void changeColor(int type);
	void changeFace(State state);
	void update(float dt, Point move);

	State _state;
};

class CFEnemy : public CEnemyObj {
private:

public:
	CFEnemy();
	~CFEnemy();
	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder = 1);
	void initState();
	void update(float dt, Point move);
	void setPosition(const cocos2d::Point pos);

	bool repeatAnim;
};

class CBEnemy : public CEnemyObj {
private:

public:
	CBEnemy();
	~CBEnemy();
	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder = 1);
	void initState();
	void update(float dt,Point move);
	void setPosition(const cocos2d::Point pos);
	void Jump(float dt, Point move);

	bool _isJump;
	bool _hightPoint;
	bool drop;

	float _jumptime;
	float _waitTime;
};

