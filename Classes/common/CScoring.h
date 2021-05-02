#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class CScoring {
private:
	int _score;

	std::string _scoreText;
	std::string _scoreString;
	std::string _timeString;
	cocos2d::Label* _scoreLabel;
	cocos2d::Label* _timeLabel;

	bool isChange;
	bool _isGameStart;
	bool _isCountStart;

	float _countTime;
	float _moveSpeed;
public:
	CScoring();
	~CScoring();

	static CScoring* create(cocos2d::Point scorePos, cocos2d::Point timePos, cocos2d::Node& parent, cocos2d::Size size, int zOrder = 11);
	static CScoring* getInstance();

	void init(cocos2d::Point scorePos, cocos2d::Point timePos, cocos2d::Node& parent, cocos2d::Size size, int zOrder);
	void initState();
	void update(float dt);
	int getScore(int score);
	void setScore(int score);
	void setChange(bool change);
	bool getChange();
	void setMoveSpeed(float speed);
	float getMoveSpeed();
	void setStart(bool start,int type=0);
	bool getStart();

	bool _isInit;
	
	int _level;
};