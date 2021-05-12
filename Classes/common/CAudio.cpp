#include "CAudio.h"

#define JumpAudio "./scene101/music/thinking cloud.mp3"
#define BgAudio "./scene101/music/sr_bg.mp3"
#define ArrivalAudio "./scene101/music/arrivalsfinalsound.mp3"
#define ScoreAudio "./scene101/music/gain point.mp3"

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
}

void CAudio::setPlay(int type, bool play) {
	if (type == 0) {
		if (play)_ijumpMusic = AudioEngine::play2d(JumpAudio, false, 0.75f);
		else AudioEngine::pause(_ijumpMusic);
	}
	else if (type == 1) {
		if (play)_iscoreMusic = AudioEngine::play2d(ScoreAudio, false, 0.75f);
		else AudioEngine::pause(_iscoreMusic);
	}
	else if (type == 2) {
		if (play)_iarrivalMusic = AudioEngine::play2d(ArrivalAudio, false, 0.75f);
		else AudioEngine::pause(_iarrivalMusic);
	}
}