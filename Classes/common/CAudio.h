#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

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