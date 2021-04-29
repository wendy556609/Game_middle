#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "common/CRoad.h"

class CMiddleObject {
private:
	CRoad* _road0, *_road1;
public:
	CMiddleObject();
	~CMiddleObject();
	void update(float dt);  // 根據時間自己移動

	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& imgname);
	void setSpeed(float speed);

	float movespeed;
};