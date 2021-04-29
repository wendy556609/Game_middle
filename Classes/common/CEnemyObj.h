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
	virtual void update(float dt)=0;

	cocostudio::timeline::ActionTimeline* _showAction;
	cocos2d::Point _initPos;
	cocos2d::Vec2 _cPos;
	float _moveSpeed;
	int blood;
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
	void update(float dt);

	State _state;
};

class CFEnemy : public CEnemyObj {
private:

public:
	CFEnemy();
	~CFEnemy();
	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder = 1);
	void initState();
	void update(float dt);
	void setPosition(const cocos2d::Point pos);

	
	bool _startAnim;

};

class CBEnemy : public CEnemyObj {
private:

public:
	CBEnemy();
	~CBEnemy();
	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder = 1);
	void initState();
	void update(float dt);
	void setPosition(const cocos2d::Point pos);
	void Jump(float dt);

	bool _startAnim;

	bool _isJump;
	bool _hightPoint;

	float _jumptime;
	float _airTime;
};

class CEnemyNode {
private:
public:
	CEnemyNode();
	~CEnemyNode();

	CEnemyObj* _enemy[3];

	void init(cocos2d::Node& parent, cocos2d::Point playerPos);
	void resetEnemyState(int type);
	void resetEnemy();
	void update(float dt);
	void pointUpdate(float dt);
	void setSpeed(float speed);
	void setPosition(Point pos);
	bool checkCollider(CGameObject& object);
	int getHurt();

	CCollider* getCollider();

	cocos2d::Point _initPoint;
	cocos2d::Point _rebornPoint;
	cocos2d::Node* _enemyNode;

	int enemyOn;
	float _moveSpeed;
};