#include "CButton.h"

CButton::CButton() {
	_normalPic = nullptr;
	_touchedPic = nullptr;
}
void CButton::init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& normalName, const std::string& touchedName, int zOrder) {
	_normalPic = Sprite::createWithSpriteFrameName(normalName + ".png");
	_touchedPic = Sprite::createWithSpriteFrameName(touchedName + ".png");
	_BtnLoc = position;
	_normalPic->setPosition(_BtnLoc);
	_touchedPic->setPosition(_BtnLoc);
	_touchedPic->setVisible(false);

	parent.addChild(_normalPic, zOrder);
	parent.addChild(_touchedPic, zOrder);

	_BtnSize = _normalPic->getContentSize();
	_BtnRect = Rect(_BtnLoc.x - _BtnSize.width / 2, _BtnLoc.y - _BtnSize.height / 2, _BtnSize.width, _BtnSize.height);

	_bTouched = false;
	_bEnabled = _bVisible = true;
}

void CButton::setEnable(bool enable) {
	_bEnabled = enable;
}

bool CJumpButton::touchesBegin(cocos2d::Point inPos) {
	if (_BtnRect.containsPoint(inPos) && _bEnabled) {
		_bTouched = true;
		_touchedPic->setVisible(true);
		_normalPic->setVisible(false);
		return true;
	}
	return false;

}

bool CJumpButton::touchesMove(cocos2d::Point inPos) {
	if (_bTouched) {
		if (!_BtnRect.containsPoint(inPos)) {
			_bTouched = false;
			_touchedPic->setVisible(false);
			_normalPic->setVisible(true);
			return false;
		}
		return true;
	}
	return false;
}

bool CJumpButton::touchesEnd(cocos2d::Point inPos) {
	if (_BtnRect.containsPoint(inPos) && _bEnabled) {
		_bTouched = false;
		return true;
	}
	return false;
}

void CJumpButton::setSprite(bool enable) {
	if (!_bTouched) {
		setEnable(enable);
		if (_bEnabled) {
			_normalPic->setVisible(true);
			_touchedPic->setVisible(false);
		}
		else {
			_touchedPic->setVisible(true);
			_normalPic->setVisible(false);
		};
	}
}

void CJumpButton::initState() {
	_normalPic->setVisible(true);
	_touchedPic->setVisible(false);
}

bool CStartButton::touchesBegin(cocos2d::Point inPos) {
	if (_BtnRect.containsPoint(inPos) && _bEnabled) {
		_bTouched = true;
		_touchedPic->setVisible(true);
		_normalPic->setVisible(false);
		return true;
	}
	return false;

}

bool CStartButton::touchesMove(cocos2d::Point inPos) {
	if (_bTouched) {
		if (!_BtnRect.containsPoint(inPos)) {
			_bTouched = false;
			_touchedPic->setVisible(false);
			_normalPic->setVisible(true);
			return false;
		}
		return true;
	}
	return false;
}

bool CStartButton::touchesEnd(cocos2d::Point inPos) {
	if (_BtnRect.containsPoint(inPos) && _bEnabled) {
		_bEnabled = false;
		_bTouched = false;
		_touchedPic->setVisible(false);
		_normalPic->setVisible(false);
		CScoring::getInstance()->setStart(true);
		return true;
	}
	return false;
}

bool CRestartButton::touchesBegin(cocos2d::Point inPos) {
	if (_BtnRect.containsPoint(inPos) && _bEnabled) {
		_bTouched = true;
		_touchedPic->setColor(Color3B(230, 230, 250));
		_touchedPic->setVisible(true);
		_normalPic->setVisible(false);
		return true;
	}
	return false;

}

bool CRestartButton::touchesMove(cocos2d::Point inPos) {
	if (_bTouched) {
		if (!_BtnRect.containsPoint(inPos)) {
			_bTouched = false;
			_touchedPic->setVisible(false);
			_normalPic->setVisible(true);
			return false;
		}
		return true;
	}
	return false;
}

bool CRestartButton::touchesEnd(cocos2d::Point inPos) {
	if (_BtnRect.containsPoint(inPos) && _bEnabled) {
		_bEnabled = false;
		_bTouched = false;
		_touchedPic->setVisible(false);
		_normalPic->setVisible(true);
		CScoring::getInstance()->setStart(false, 1);
		return true;
	}
	return false;
}

bool CRunButton::touchesBegin(cocos2d::Point inPos) {
	if (_BtnRect.containsPoint(inPos) && _bEnabled) {
		if (!CScoring::getInstance()->getChange()) {
			CScoring::getInstance()->setMoveSpeed(3.5f);
		}
		_bTouched = true;
		_touchedPic->setVisible(true);
		_normalPic->setVisible(false);
		return true;
	}
	return false;

}

bool CRunButton::touchesMove(cocos2d::Point inPos) {
	if (_bTouched) {
		if (!_BtnRect.containsPoint(inPos)) {
			_bTouched = false;
			_touchedPic->setVisible(false);
			_normalPic->setVisible(true);
			return false;
		}
		return true;
	}
	return false;
}

bool CRunButton::touchesEnd(cocos2d::Point inPos) {
	if (_BtnRect.containsPoint(inPos) && _bEnabled) {
		CScoring::getInstance()->setMoveSpeed(2.0f);
		_bTouched = false;
		_touchedPic->setVisible(false);
		_normalPic->setVisible(true);
		return true;
	}
	return false;
}