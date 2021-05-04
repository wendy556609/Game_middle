#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "common/CScoring.h"

USING_NS_CC;

class CButton {
private:

public:
	CButton();
	virtual void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& normalName, const std::string& touchedName, int zOrder = 11);
	virtual bool touchesBegin(cocos2d::Point inPos) = 0;
	virtual bool touchesMove(cocos2d::Point inPos) = 0;
	virtual bool touchesEnd(cocos2d::Point inPos) = 0;
	void setEnable(bool enable);
	void setVisible(bool visible) {
		_normalPic->setVisible(visible);
	}
	virtual void initState() {};

	bool _bTouched; // 是否被按下
	bool _bEnabled; // 是否有作用
	bool _bVisible; // 是否顯示
protected:
	cocos2d::Sprite* _normalPic;
	cocos2d::Sprite* _touchedPic;

	cocos2d::Size  _BtnSize;
	cocos2d::Point _BtnLoc;
	cocos2d::Rect  _BtnRect;
};
class CJumpButton :public CButton {
private:
public:
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMove(cocos2d::Point inPos);
	bool touchesEnd(cocos2d::Point inPos);
	void setSprite(bool enable);
	void initState();
};

class CStartButton :public CButton {
private:
public:
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMove(cocos2d::Point inPos);
	bool touchesEnd(cocos2d::Point inPos);
};

class CRestartButton :public CButton {
private:
public:
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMove(cocos2d::Point inPos);
	bool touchesEnd(cocos2d::Point inPos);
};

class CRunButton :public CButton {
private:
public:
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMove(cocos2d::Point inPos);
	bool touchesEnd(cocos2d::Point inPos);
};

class CBoardButton :public CButton {
private:
	bool isOpen = false;
public:
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMove(cocos2d::Point inPos);
	bool touchesEnd(cocos2d::Point inPos);
	void initState();
};