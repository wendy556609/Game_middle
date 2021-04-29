#pragma once // �@�ӫD�зǦ��O�Q�s�x�䴩���e�m�B�z�Ÿ��A�����ɮ׸��J���l�ɮɡA�u�|�b�ӭ�l�ɤ��Q�]�t�@��

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
	void update(float dt);  // �ھڮɶ��ۤv����

	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& imgname);
	void setSpeed(float speed);

	float movespeed;
};