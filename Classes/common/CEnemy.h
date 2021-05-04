#pragma once // �@�ӫD�зǦ��O�Q�s�x�䴩���e�m�B�z�Ÿ��A�����ɮ׸��J���l�ɮɡA�u�|�b�ӭ�l�ɤ��Q�]�t�@��

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CEnemyObj.h"
#include "CScoring.h"

USING_NS_CC;

class CEnemyNode {
private:
public:
	CEnemyNode();
	~CEnemyNode();

	CEnemyObj* _enemy[3];

	void init(cocos2d::Node& parent, cocos2d::Point start);
	void initState();

	void resetEnemyState(int type);
	void resetEnemy();

	void update(float dt);
	void pointUpdate(float dt);

	void setSpeed(float speed);

	bool checkCollider(CGameObject& object);
	int getHurt();
	int getPassScore();
	CCollider* getCollider();

	cocos2d::Point _startPoint;
	cocos2d::Point _initPoint;
	cocos2d::Point _rebornPoint;
	cocos2d::Point _enemyNode;

	int enemyOn;

	float _moveSpeed;
	float waitTime;

	bool isStart;
	bool isPass;
};

class CEnemy {
private:
public:
	CEnemy();
	~CEnemy();

	CEnemyNode* _enemyNode[3];

	void init(cocos2d::Node& parent, cocos2d::Point playerPoint);
	void initState();

	void update(float dt);
	void setSpeed(float speed);

	bool checkCollider(CGameObject& object);
	int getHurt();
	bool passPlayer(CGameObject& object);
	int getPassScore();

	int blood;
};