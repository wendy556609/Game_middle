#pragma once // 一個非標準但是被廣泛支援的前置處理符號，讓該檔案載入到原始檔時，只會在該原始檔內被包含一次

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class CRoad {
private:
	cocos2d::Point    genLoc[3]; // 生成在 road 上裝飾物的 x 座標 與 y 座標
	cocos2d::Sprite* _road;  // 兩段道路, 圖片來源都是 road00.png
	cocos2d::Node* _roadobj[3]; // 兩段道路上的三個裝飾物件
	int _iroadon[3]; // 紀錄目前每一個生成點,顯示的是哪一個物件
	cocos2d::Point _initPos;

public:
	CRoad();
	~CRoad();
	void update(float dt);  // 根據時間自己移動

	void init(const cocos2d::Point position, cocos2d::Node& parent, const std::string& imgname);
	void resetObj();
	void setSpeed(float speed);
	void initState();

	float movespeed;
};