#pragma once // �@�ӫD�зǦ��O�Q�s�x�䴩���e�m�B�z�Ÿ��A�����ɮ׸��J���l�ɮɡA�u�|�b�ӭ�l�ɤ��Q�]�t�@��

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

class CButton {
private:
	
public:
	CButton();
	virtual void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& normalName, const std::string& touchedName, int zOrder = 11);
	virtual bool touchesBegin(cocos2d::Point inPos )= 0;
	virtual bool touchesMove(cocos2d::Point inPos) = 0;
	virtual bool touchesEnd(cocos2d::Point inPos) = 0;
	void setEnable(bool enable);

	bool _bTouched; // �O�_�Q���U
	bool _bEnabled; // �O�_���@��
	bool _bVisible; // �O�_���
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
};

class C3SButton {
private:
public:
	enum BtnType {
		jumpBtn,
		returnBtn,
	};

	C3SButton();
	~C3SButton();

	CJumpButton* _jumpButton;
	void init(const BtnType type, const cocos2d::Point position, cocos2d::Node& parent, const std::string& normalName, const std::string& touchedName, int zOrder = 11);
	bool touchesBegin(const BtnType type,cocos2d::Point inPos);
	bool touchesMove(const BtnType type,cocos2d::Point inPos);
	bool touchesEnd(const BtnType type,cocos2d::Point inPos);
	void setEnable(const BtnType type, bool enable);
};