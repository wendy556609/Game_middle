#include "CAudio.h"

#define JumpAudio "./scene101/music/thinking cloud.wav"
#define BgAudio "./scene101/music/sr_bg.mp3"
#define ArrivalAudio "./scene101/music/arrivalsfinalsound.wav"
#define ScoreAudio "./scene101/music/gain point.wav"

CAudio::CAudio() {
	_ibgMusic = -1;
	_ijumpMusic = 1;
	_iscoreMusic = 1;
	_iarrivalMusic = 1;
}

CAudio::~CAudio() {

}

void CAudio::init() {
	_ibgMusic = AudioEngine::play2d(BgAudio, true, 0.75f);

	_ijumpMusic = SimpleAudioEngine::getInstance()->playEffect(JumpAudio, false);
	SimpleAudioEngine::getInstance()->pauseEffect(_ijumpMusic);

	_iscoreMusic = SimpleAudioEngine::getInstance()->playEffect(ScoreAudio, false);
	SimpleAudioEngine::getInstance()->pauseEffect(_iscoreMusic);

	_iarrivalMusic = SimpleAudioEngine::getInstance()->playEffect(ArrivalAudio, false);
	SimpleAudioEngine::getInstance()->pauseEffect(_iarrivalMusic);
}

void CAudio::setPlay(int type, bool play) {
	if (type == 0) {
		if (play)SimpleAudioEngine::getInstance()->rewindEffect(_ijumpMusic, false);
		else SimpleAudioEngine::getInstance()->pauseEffect(_ijumpMusic);
	}
	else if (type == 1) {
		if (play)SimpleAudioEngine::getInstance()->rewindEffect(_iscoreMusic, false);
		else SimpleAudioEngine::getInstance()->pauseEffect(_iscoreMusic);
	}
	else if (type == 2) {
		if (play)SimpleAudioEngine::getInstance()->rewindEffect(_iarrivalMusic, false);
		else SimpleAudioEngine::getInstance()->pauseEffect(_iarrivalMusic);
	}
}