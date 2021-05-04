#include "CEnemy.h"

CEnemyNode::CEnemyNode() {
	_enemy[0] = _enemy[1] = _enemy[2] = nullptr;

	_initPoint = Vec2(-1080, 124);
	enemyOn = 0;
	_moveSpeed = 1;
	waitTime = 0;

	isStart = true;
	isPass = false;
}

CEnemyNode::~CEnemyNode() {
	CC_SAFE_DELETE(_enemy[0]);
	CC_SAFE_DELETE(_enemy[1]);
	CC_SAFE_DELETE(_enemy[2]);
}

void CEnemyNode::init(cocos2d::Node& parent, cocos2d::Point start) {
	Point position;
	_startPoint = start;
	position = _startPoint;
	_enemyNode = position;
	//tri
	_enemy[0] = new (std::nothrow)CTriEnemy();
	_enemy[0]->init(position, parent, "triangle_node.csb", "collider", 3);
	_enemy[0]->setVisible(false);
	_enemy[0]->setEnable(false);
	//bean
	_enemy[2] = new (std::nothrow)CBEnemy();
	_enemy[2]->init(position, parent, "bean_jump.csb", "collider", 3);
	_enemy[2]->setVisible(false);
	_enemy[2]->setEnable(false);
	//fire
	position.y = 165;
	_enemy[1] = new (std::nothrow)CFEnemy();
	_enemy[1]->init(position, parent, "fire.csb", "collider", 3);
	_enemy[1]->setVisible(false);
	_enemy[1]->setEnable(false);

	resetEnemy();
}

void CEnemyNode::initState() {
	_enemyNode = _startPoint;
	_enemy[0]->initState();
	_enemy[1]->initState();
	_enemy[2]->initState();
	resetEnemy();
}

void CEnemyNode::resetEnemyState(int type) {
	_enemy[enemyOn]->setVisible(false);
	_enemy[enemyOn]->setEnable(false);

	enemyOn = type;
	_enemy[enemyOn]->initState();
	_enemy[enemyOn]->setVisible(true);
	_enemy[enemyOn]->setEnable(true);
}

void CEnemyNode::resetEnemy() {
	int level = CScoring::getInstance()->getLevel();
	int enemyType = rand() % level;
	resetEnemyState(enemyType);
	int range = 100 - (rand() % 200);
	_rebornPoint.x = _initPoint.x + range;

	isStart = false;
	isPass = false;
}

void CEnemyNode::update(float dt) {
	if (!isStart) {
		waitTime += dt;
		if (waitTime >= 1.0f) {
			isStart = true;
		}
	}
	else {
		pointUpdate(dt);
	}
}

void CEnemyNode::pointUpdate(float dt) {
	Point pt = _enemyNode;

	pt.x += dt * _moveSpeed;

	if (pt.x >= 1350) {
		resetEnemy();
		pt.x = _rebornPoint.x;
	}
	_enemyNode = pt;
	_enemy[enemyOn]->update(dt, _enemyNode);
}

void CEnemyNode::setSpeed(float speed) {
	_moveSpeed = speed;
}

bool CEnemyNode::checkCollider(CGameObject& object) {
	if (_enemy[enemyOn]->OnColliderCheck(*object.getCollider())) {
		return true;
	}
	else {
		return false;
	}
}

CCollider* CEnemyNode::getCollider() {
	return _enemy[enemyOn]->getCollider();
}

int CEnemyNode::getHurt() {
	return _enemy[enemyOn]->blood;
}
int CEnemyNode::getPassScore() {
	return _enemy[enemyOn]->enemyScore;
}

CEnemy::CEnemy() {
	_enemyNode[0] = _enemyNode[1] = _enemyNode[2] = nullptr;
	blood = 0;
}

CEnemy::~CEnemy() {
	CC_SAFE_DELETE(_enemyNode[0]);
	CC_SAFE_DELETE(_enemyNode[1]);
	CC_SAFE_DELETE(_enemyNode[2]);
}

void CEnemy::init(cocos2d::Node& parent, cocos2d::Point playerPoint) {
	_enemyNode[0] = new(std::nothrow)CEnemyNode();
	_enemyNode[0]->init(parent, Vec2(-200, playerPoint.y));

	_enemyNode[1] = new(std::nothrow)CEnemyNode();
	_enemyNode[1]->init(parent, Vec2(-1080, playerPoint.y));

	_enemyNode[2] = new(std::nothrow)CEnemyNode();
	_enemyNode[2]->init(parent, Vec2(-1960, playerPoint.y));
}

void CEnemy::update(float dt) {
	_enemyNode[0]->update(dt);
	_enemyNode[1]->update(dt);
	_enemyNode[2]->update(dt);
}
void CEnemy::setSpeed(float speed) {
	_enemyNode[0]->setSpeed(speed);
	_enemyNode[1]->setSpeed(speed);
	_enemyNode[2]->setSpeed(speed);
}
bool CEnemy::checkCollider(CGameObject& object) {
	if (_enemyNode[0]->checkCollider(object)) {
		blood = _enemyNode[0]->getHurt();
		return true;
	}
	else if (_enemyNode[1]->checkCollider(object)) {
		blood = _enemyNode[1]->getHurt();
		return true;
	}
	else if (_enemyNode[2]->checkCollider(object)) {
		blood = _enemyNode[2]->getHurt();
		return true;
	}
	else {
		blood = 0;
		return false;
	}
	
}
int CEnemy::getHurt() {
	return blood;
}

bool CEnemy::passPlayer(CGameObject& object) {
	if (!_enemyNode[0]->isPass&&_enemyNode[0]->_enemyNode.x>= object.getPosition().x) {
		_enemyNode[0]->isPass = true;
		return true;
	}
	else if (!_enemyNode[1]->isPass && _enemyNode[1]->_enemyNode.x >= object.getPosition().x) {
		_enemyNode[1]->isPass = true;
		return true;
	}
	else if (!_enemyNode[2]->isPass && _enemyNode[2]->_enemyNode.x >= object.getPosition().x) {
		_enemyNode[2]->isPass = true;
		return true;
	}
	return false;
}

int CEnemy::getPassScore() {
	if (_enemyNode[0]->isPass) {
		return _enemyNode[0]->getPassScore();
	}
	else if (_enemyNode[1]->isPass) {
		return _enemyNode[1]->getPassScore();
	}
	else if (_enemyNode[2]->isPass) {
		return _enemyNode[2]->getPassScore();
	}
	else return 0;
}

void CEnemy::initState() {
	blood = 0;
	_enemyNode[0]->initState();
	_enemyNode[1]->initState();
	_enemyNode[2]->initState();
}