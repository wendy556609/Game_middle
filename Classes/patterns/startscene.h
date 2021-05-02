#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "./common/C3SButton.h"

class StartScene :public cocos2d::Scene {
private:
	bool _bToGameScene;
public:
	StartScene();
	~StartScene();

	static cocos2d::Scene* createScene();
	virtual bool init();

	C3SButton* btn;

	void update(float dt);

	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	
	CREATE_FUNC(StartScene);
};