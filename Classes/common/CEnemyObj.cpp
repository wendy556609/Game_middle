#include "CEnemyObj.h"

CTriEnemy::CTriEnemy() {
	_showAction = nullptr;
	blood = 1;
}
CTriEnemy::~CTriEnemy() {

}

void CTriEnemy::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder) {
	_position = position;
	_initPos = position;
	_objectNode = CSLoader::createNode(csbname);
	_size = _objectNode->getChildByName(layername)->getContentSize();
	initBoxCollider(position, _size);
	setPosition(position);
	parent.addChild(_objectNode, zOrder);

	_showAction = CSLoader::createTimeline(csbname);
	_objectNode->runAction(_showAction);
	
	initState();

	_moveSpeed = 150;
}

void CTriEnemy::initState() {
	int face = rand() % 2;
	int color = rand() % 3;

	changeFace(State(face));
	changeColor(color);

	_showAction->gotoFrameAndPlay(0, 35, false);
	_showAction->setTimeSpeed(1.0f);
}

void CTriEnemy::changeColor(int type) {
	if (type == 0) {
		_objectNode->setColor(Color3B(40, 91, 143));
	}
	if (type == 1) {
		_objectNode->setColor(Color3B(180, 53, 44));
	}
	if (type == 2) {
		_objectNode->setColor(Color3B(134, 140, 43));
	}
}

void CTriEnemy::changeFace(State state) {
	_state = state;
	if (_state == State::happy) {
		_objectNode->getChildByName("triblock_1")->getChildByName("happyface")->setVisible(true);
		_objectNode->getChildByName("triblock_1")->getChildByName("sadface")->setVisible(false);
	}
	else if (_state == State::sad) {
		_objectNode->getChildByName("triblock_1")->getChildByName("happyface")->setVisible(false);
		_objectNode->getChildByName("triblock_1")->getChildByName("sadface")->setVisible(true);
	}
}

void CTriEnemy::update(float dt) {
}

CFEnemy::CFEnemy() {
	_showAction = nullptr;
	_startAnim = false;
	blood = 2;
}

CFEnemy::~CFEnemy() {

}

void CFEnemy::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder) {
	_position = position;
	_initPos = position;
	_objectNode = CSLoader::createNode(csbname);
	_size = _objectNode->getChildByName(layername)->getContentSize();
	_cPos = _objectNode->getChildByName(layername)->getPosition();
	initBoxCollider(position+ _cPos, _size);
	setPosition(position);
	parent.addChild(_objectNode, zOrder);

	_showAction = CSLoader::createTimeline(csbname);
	_objectNode->runAction(_showAction);

	initState();
}

void CFEnemy::setPosition(const cocos2d::Point pos) {
	_position = pos;
	_objectNode->setPosition(pos);
	setBoxCollider(pos + _cPos, _size);
}

void CFEnemy::initState() {
	setPosition(_initPos);

	_showAction->gotoFrameAndPlay(0, 30, false);
	_showAction->setTimeSpeed(1.0f);
	_startAnim = false;
}

void CFEnemy::update(float dt) {
	if (_showAction->getCurrentFrame() == 30&& !_startAnim) {
		_showAction->gotoFrameAndPlay(30, 60, true);
		_startAnim = true;
	}
}

CBEnemy::CBEnemy() {
	_showAction = nullptr;
	_startAnim = false;

	_isJump = false;
	_hightPoint = false;
	_jumptime = 0;
	_airTime = 0;
	blood = 3;
}

CBEnemy::~CBEnemy() {

}

void CBEnemy::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder) {
	_position = position;
	_objectNode = CSLoader::createNode(csbname);
	_size = _objectNode->getChildByName(layername)->getContentSize();
	_cPos = _objectNode->getChildByName(layername)->getPosition();
	_initPos = position + _cPos;
	initBoxCollider(position + _cPos, _size);
	setPosition(position);
	parent.addChild(_objectNode, zOrder);

	_showAction = CSLoader::createTimeline(csbname);
	_objectNode->runAction(_showAction);

	initState();
}

void CBEnemy::initState() {
	setPosition(_initPos);

	_showAction->gotoFrameAndPlay(0, 18, false);
	_isJump = false;
	_hightPoint = false;
	_jumptime = 0;
	_airTime = 0;
	//_showAction->setTimeSpeed(1.0f);
	//_startAnim = false;
}

void CBEnemy::setPosition(const cocos2d::Point pos) {
	_position = pos;
	_objectNode->setPosition(pos);
	setBoxCollider(pos + _cPos, _size);
}

void CBEnemy::update(float dt) {
	Jump(dt);
}

void CBEnemy::Jump(float dt) {
		_jumptime += dt;
		float ph = sinf(_jumptime * M_PI / 1.0f);
		Point pos = Vec2(getPosition().x, _initPos.y + ph * 250);
		setPosition(pos);
		if (ph ==1) {
			_showAction->gotoFrameAndPlay(18, 30, false);
		}
		if (_jumptime > 1.0f) {
			_jumptime = 0;
			setPosition(Vec2(getPosition().x, _initPos.y));
			_showAction->setTimeSpeed(1.0f);
			_showAction->gotoFrameAndPlay(0, 18, false);
		}
}

CEnemyNode::CEnemyNode() {
	_enemy[0] = _enemy[1] = _enemy[2] = nullptr;
	_initPoint = Vec2(200, 124);
	enemyOn = 0;
	_enemyNode = nullptr;
	_moveSpeed = 150;
}

CEnemyNode::~CEnemyNode() {
	CC_SAFE_DELETE(_enemy[0]);
	CC_SAFE_DELETE(_enemy[1]);
	CC_SAFE_DELETE(_enemy[2]);
}

void CEnemyNode::init(cocos2d::Node& parent, cocos2d::Point playerPos) {
	Point position;
	position = _initPoint;
	_enemyNode = new (std::nothrow)Node();
	position.y = playerPos.y;
	//tri
	_enemy[0] = new (std::nothrow)CTriEnemy();
	_enemy[0]->init(Vec2(0,0), *_enemyNode, "triangle_node.csb", "triblock_1", 3);
	_enemy[0]->setVisible(false);
	//bean
	_enemy[2] = new (std::nothrow)CBEnemy();
	_enemy[2]->init(Vec2(0, 0), *_enemyNode, "bean_jump.csb", "collider", 3);
	_enemy[2]->setVisible(false);
	//fire
	_enemy[1] = new (std::nothrow)CFEnemy();
	_enemy[1]->init(Vec2(0, 165-playerPos.y), *_enemyNode, "fire.csb", "collider", 3);
	_enemy[1]->setVisible(false);

	parent.addChild(_enemyNode, 3);
	_enemyNode->setPosition(position);
	resetEnemy();
}

void CEnemyNode::resetEnemyState(int type) {
	_enemy[enemyOn]->setVisible(false);

	enemyOn = type;
	_enemy[enemyOn]->initState();
	_enemy[enemyOn]->setVisible(true);
}

void CEnemyNode::resetEnemy() {
	int enemyType = rand() % 3;
	resetEnemyState(enemyType);
	int range = 50-(rand() % 100);
	_rebornPoint.x = _initPoint.x + range;
}

void CEnemyNode::update(float dt) {
	pointUpdate(dt);
}

void CEnemyNode::pointUpdate(float dt) {
	Point pt = _enemyNode->getPosition();
	pt.x += dt * _moveSpeed;
	_enemy[enemyOn]->update(dt);
	if (pt.x >= 1280) {
		pt.x = _rebornPoint.x;
		resetEnemy();
	}
	_enemyNode->setPosition(pt);
}

void CEnemyNode::setSpeed(float speed) {
	_moveSpeed = 150 * speed;
}

void CEnemyNode::setPosition(Point pos) {
	_enemyNode->setPosition(pos);
}

bool CEnemyNode::checkCollider(CGameObject& object) {
	if (_enemy[enemyOn]->OnColliderCheck(*object.getCollider())) {
		log("collider");
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