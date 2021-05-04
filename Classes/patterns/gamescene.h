#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "./common/C3SButton.h"
#include "patterns/CRunner.h"
#include "common/CMiddleObject.h"
#include "common/CEnemy.h"
#include "common/CScoring.h"
#include "common/CCanvas.h"

class GameScene :public cocos2d::Scene {
private:
public:
	GameScene();
	~GameScene();

	static cocos2d::Scene* createScene();
	virtual bool init();

	CRunner* _runner;
	CMiddleObject* _midObj;
	C3SButton* _c3sButton;
	CEnemy* _enemy;
	CCanvas* _Bar;

	void update(float dt);

	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	CREATE_FUNC(GameScene);
};