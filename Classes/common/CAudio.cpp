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

	_ijumpMusic = SimpleAudioEngine::sharedEngine()->playEffect(JumpAudio, false);
	SimpleAudioEngine::sharedEngine()->pauseEffect(_ijumpMusic);

	_iscoreMusic = SimpleAudioEngine::sharedEngine()->playEffect(ScoreAudio, false);
	SimpleAudioEngine::sharedEngine()->pauseEffect(_iscoreMusic);

	_iarrivalMusic = SimpleAudioEngine::sharedEngine()->playEffect(ArrivalAudio, false);
	SimpleAudioEngine::sharedEngine()->pauseEffect(_iarrivalMusic);
}

void CAudio::setPlay(int type, bool play) {
	if (type == 0) {
		if (play)SimpleAudioEngine::sharedEngine()->rewindEffect(_ijumpMusic, false);
		else SimpleAudioEngine::sharedEngine()->pauseEffect(_ijumpMusic);
	}
	else if (type == 1) {
		if (play)SimpleAudioEngine::sharedEngine()->rewindEffect(_iscoreMusic, false);
		else SimpleAudioEngine::sharedEngine()->pauseEffect(_iscoreMusic);
	}
	else if (type == 2) {
		if (play)SimpleAudioEngine::sharedEngine()->rewindEffect(_iarrivalMusic, false);
		else SimpleAudioEngine::sharedEngine()->pauseEffect(_iarrivalMusic);
	}
}