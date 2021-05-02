//#include "CGameManager.h"
//
//CGameManager::CGameManager() {
//	_GameManager = nullptr;
//}
//CGameManager::~CGameManager() {
//	CC_SAFE_DELETE(_GameManager);
//}
//
//void CGameManager::init() {
//	_score = 0;
//}
//
//CGameManager* CGameManager::getInstance() {
//	if (!_GameManager) {
//		_GameManager = new(std::nothrow)CGameManager;
//		_GameManager->init();
//	}
//	return _GameManager;
//}
//
//int CGameManager::getScore(int score) {
//	return _score;
//}
//
//void CGameManager::setScore(int score) {
//	_score += score;
//}