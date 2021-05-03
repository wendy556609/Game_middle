#pragma once // �@�ӫD�зǦ��O�Q�s�x�䴩���e�m�B�z�Ÿ��A�����ɮ׸��J���l�ɮɡA�u�|�b�ӭ�l�ɤ��Q�]�t�@��

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "common/CButton.h"

USING_NS_CC;


class C3SButton {
private:
	C3SButton* buttons;
public:
	enum BtnType {
		all,
		startBtn,
		jumpBtn,
		restartBtn,
		runBtn,
		boardBtn
	};

	C3SButton();
	~C3SButton();

	CStartButton* _startButton;
	CJumpButton* _jumpButton;
	CRestartButton* _restartButton;
	CRunButton* _runButton;
	CBoardButton* _boardButton;
	
	void init(const BtnType type, const cocos2d::Point position, cocos2d::Node& parent, const std::string& normalName, const std::string& touchedName, int zOrder = 11);
	bool touchesBegin(cocos2d::Point inPos,BtnType type= BtnType::all);
	bool touchesMove(cocos2d::Point inPos, BtnType type = BtnType::all);
	bool touchesEnd(cocos2d::Point inPos, BtnType type = BtnType::all);
	void setEnable(bool enable, BtnType type = BtnType::all);
	void setVisible(bool visible);
	void initState();
};