#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "common/CScoring.h"

class CBar {
protected:
	cocos2d::Size _initSize;
	cocos2d::Size _barSize;

	cocos2d::Point _initPos;
	cocos2d::Point _movePos;
public:
	CBar();
	~CBar();

	void init(cocos2d::Point pos, cocos2d::Node& parent, float initValue, cocos2d::Vec2 size, int zOrder);
	void initState();
	void setBar(int value);

	cocos2d::Sprite* _barBase;
	cocos2d::Sprite* _barSprite;

	float _initValue;
	float _currentValue;
};

class CTimeBar: public  CBar{
private:
	cocos2d::Sprite* _timeBarIcon;
public:
	CTimeBar();
	~CTimeBar() {};

	void initAll(cocos2d::Point pos, cocos2d::Node& parent, float initValue, cocos2d::Vec2 size, int zOrder);
	void initTimeState();
	void setTimeBar(int value);
};

class CCanvas{
private:
	CBar* _bloodBar;
	CTimeBar* _timeBar;
public:
	CCanvas();
	~CCanvas();

	/*type-1_blood type-2_time*/
	void init(int type,cocos2d::Point pos, cocos2d::Node& parent, int zOrder = 11);
	void initState();
	void setBlood(int blood);
	void update();
};