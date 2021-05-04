#pragma once // �@�ӫD�зǦ��O�Q�s�x�䴩���e�m�B�z�Ÿ��A�����ɮ׸��J���l�ɮɡA�u�|�b�ӭ�l�ɤ��Q�]�t�@��

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

class CAudio {
private:
	int _ijumpMusic;
	int _ibgMusic;
	int _iscoreMusic;
	int _iarrivalMusic;
public:
	CAudio();
	~CAudio();

	void init();
	/*0_jump 1_score 2_arrival*/
	void setPlay(int type, bool play);
};