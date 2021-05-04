#pragma once // �@�ӫD�зǦ��O�Q�s�x�䴩���e�m�B�z�Ÿ��A�����ɮ׸��J���l�ɮɡA�u�|�b�ӭ�l�ɤ��Q�]�t�@��

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CAudio.h"

#define FINALTIME 60
#define TOTBLOOD 10

class CScoreBoard {
private:
	cocos2d::Sprite* _board;
	cocos2d::Label* _medals[3];
	int _bestScore[3];
	
public:
	CScoreBoard();
	~CScoreBoard();

	void init(cocos2d::Node& parent, int zOrder);
	void setVisible(bool visible);
	void checkBestScore(int score);
	void setString();
};

class CScoring {
private:
	int _score;
	int _level;

	std::string _scoreText;
	std::string _levelText;
	std::string _scoreString;
	std::string _timeString;
	std::string _levelString;
	std::string _endString;
	
	cocos2d::Label* _scoreLabel;
	cocos2d::Label* _timeLabel;
	cocos2d::Label* _levelLabel;
	cocos2d::Label* _endLabel;

	bool isChange;
	bool _isGameStart;
	bool _isCountStart;

	float _countTime;
	float _moveSpeed;
	float _finalTime;
	float _currentTime;

	CScoreBoard* _scoreBoard;
	CAudio* _audio;
public:
	CScoring();
	~CScoring();

	static CScoring* create();
	static CScoring* getInstance();

	void init(int type, cocos2d::Point pos, cocos2d::Node& parent, int zOrder = 11);
	void initState();
	void update(float dt);

	void setScore(int score);
	void setChange(bool change);
	void setMoveSpeed(float speed);
	void setStart(bool start,int type=0);
	void setLevel();
	void setTime(float time);
	void setBoardVisible(bool visible);
	void setGameOver(float time);
	/*0_jump 1_score 2_arrival*/
	void setPlay(int type, bool play);

	int getScore();
	bool getChange();
	float getMoveSpeed();
	bool getStart();
	int getLevel();
	float getTime();

	bool _isInit;
	bool _isFinal;
	bool _isGameOver;

	int currentScore;
};