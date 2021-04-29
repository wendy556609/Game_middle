#pragma once // �@�ӫD�зǦ��O�Q�s�x�䴩���e�m�B�z�Ÿ��A�����ɮ׸��J���l�ɮɡA�u�|�b�ӭ�l�ɤ��Q�]�t�@��

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CGameObject.h"

class CShadow : public CGameObject {
public:
	CShadow();
	~CShadow();
	void setTarget(cocos2d::Point target, cocos2d::Vec2 relativePos);

	cocos2d::Point _target;
	cocos2d::Vec2 _relativePos;
};

class CRunner : public CGameObject
{
private:
	
public:
	enum State{
		normal,
		happy,
		sad
	};
	CRunner();
	~CRunner();
	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& csbname, const std::string& layername, int zOrder = 1);
	void setPosition(const cocos2d::Point pos);
	void changeFace();
	void setState(State state);
	void jumpAction(float dt);
	void update(float dt);

	State _state;
	CShadow* _shadow;
	cocostudio::timeline::ActionTimeline* _runAction;
	cocos2d::Point _initPos;
	cocos2d::Vec2 _cPos;
	bool _isJump;
	bool _hightPoint;

	bool _isHurt;
	float _jumptime;
	float _airTime;
};

