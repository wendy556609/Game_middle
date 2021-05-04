#include "C3SButton.h"

C3SButton::C3SButton() {
	_jumpButton = nullptr;
	_startButton = nullptr;
	_restartButton = nullptr;
	_runButton = nullptr;
	_boardButton = nullptr;
}
C3SButton::~C3SButton() {
	CC_SAFE_DELETE(_jumpButton);
	CC_SAFE_DELETE(_startButton);
	CC_SAFE_DELETE(_restartButton);
	CC_SAFE_DELETE(_runButton);
	CC_SAFE_DELETE(_boardButton);
}
void C3SButton::init(const BtnType type,const cocos2d::Point position, cocos2d::Node& parent, const std::string& normalName, const std::string& touchedName, int zOrder) {
	if (type == BtnType::jumpBtn) {
		_jumpButton = new (std::nothrow)CJumpButton();
		_jumpButton->init(position, parent, normalName, touchedName);
	}
	else if (type == BtnType::startBtn) {
		_startButton = new (std::nothrow)CStartButton();
		_startButton->init(position, parent, normalName, touchedName);
	}
	else if (type == BtnType::restartBtn) {
		_restartButton = new (std::nothrow)CRestartButton();
		_restartButton->init(position, parent, normalName, touchedName);
	}
	else if (type == BtnType::runBtn) {
		_runButton = new (std::nothrow)CRunButton();
		_runButton->init(position, parent, normalName, touchedName);
	}
	else if (type == BtnType::boardBtn) {
		_boardButton = new (std::nothrow)CBoardButton();
		_boardButton->init(position, parent, normalName, touchedName);
	}
}
bool C3SButton::touchesBegin(cocos2d::Point inPos, BtnType type) {
	if (type == BtnType::all) {
		_jumpButton->touchesBegin(inPos);
		_startButton->touchesBegin(inPos);
		_restartButton->touchesBegin(inPos);
		_runButton->touchesBegin(inPos);
		_boardButton->touchesBegin(inPos);
	}
	else if (type == BtnType::jumpBtn)return _jumpButton->touchesBegin(inPos);
	else if (type == BtnType::startBtn)return _startButton->touchesBegin(inPos);
	else if (type == BtnType::restartBtn)return _restartButton->touchesBegin(inPos);
	else if (type == BtnType::runBtn)return _runButton->touchesBegin(inPos);
	else if (type == BtnType::boardBtn)return _boardButton->touchesBegin(inPos);
	else return false;
}
bool C3SButton::touchesMove(cocos2d::Point inPos, BtnType type) {
	if (type == BtnType::all) {
		_jumpButton->touchesMove(inPos);
		_startButton->touchesMove(inPos);
		_restartButton->touchesMove(inPos);
		_runButton->touchesMove(inPos);
		_boardButton->touchesMove(inPos);
	}
	else if (type == BtnType::jumpBtn)return _jumpButton->touchesMove(inPos);
	else if (type == BtnType::startBtn)return _startButton->touchesMove(inPos);
	else if (type == BtnType::restartBtn)return _restartButton->touchesMove(inPos);
	else if (type == BtnType::runBtn)return _runButton->touchesMove(inPos);
	else if (type == BtnType::boardBtn)return _boardButton->touchesMove(inPos);
	else return false;
}
bool C3SButton::touchesEnd(cocos2d::Point inPos, BtnType type) {
	if (type == BtnType::all) {
		_jumpButton->touchesEnd(inPos);
		_startButton->touchesEnd(inPos);
		_restartButton->touchesEnd(inPos);
		_runButton->touchesEnd(inPos);
		_boardButton->touchesEnd(inPos);
	}
	else if (type == BtnType::jumpBtn)return _jumpButton->touchesEnd(inPos);
	else if (type == BtnType::startBtn)return _startButton->touchesEnd(inPos);
	else if (type == BtnType::restartBtn)return _restartButton->touchesEnd(inPos);
	else if (type == BtnType::runBtn)return _runButton->touchesEnd(inPos);
	else if (type == BtnType::boardBtn)return _boardButton->touchesEnd(inPos);
	else return false;
}
void C3SButton::setEnable(bool enable, const BtnType type) {
	if (type == BtnType::all) {
		_jumpButton->setEnable(enable);
		_restartButton->setEnable(enable);
		_runButton->setEnable(enable);
	}
	else if (type == BtnType::jumpBtn)_jumpButton->setSprite(enable);
	else if (type == BtnType::startBtn)_startButton->setEnable(enable);
	else if (type == BtnType::restartBtn)_restartButton->setEnable(enable);
	else if (type == BtnType::runBtn)_runButton->setEnable(enable);
	else if (type == BtnType::boardBtn) {
		_boardButton->setEnable(enable);
		_boardButton->initState();
	}
}

void C3SButton::setVisible(bool visible) {
	_startButton->setVisible(visible);
}

void C3SButton::initState() {
	_jumpButton->initState();
	_startButton->setVisible(true);

	setEnable(false);
	setEnable(true, startBtn);
}