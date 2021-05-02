#pragma once // �@�ӫD�зǦ��O�Q�s�x�䴩���e�m�B�z�Ÿ��A�����ɮ׸��J���l�ɮɡA�u�|�b�ӭ�l�ɤ��Q�]�t�@��

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class CRoad {
private:
	cocos2d::Point    genLoc[3]; // �ͦ��b road �W�˹����� x �y�� �P y �y��
	cocos2d::Sprite* _road;  // ��q�D��, �Ϥ��ӷ����O road00.png
	cocos2d::Node* _roadobj[3]; // ��q�D���W���T�Ӹ˹�����
	int _iroadon[3]; // �����ثe�C�@�ӥͦ��I,��ܪ��O���@�Ӫ���
	cocos2d::Point _initPos;

public:
	CRoad();
	~CRoad();
	void update(float dt);  // �ھڮɶ��ۤv����

	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& imgname);
	void resetObj();
	void setSpeed(float speed);
	void initState();

	float movespeed;
};