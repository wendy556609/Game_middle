/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __SCENE_102_H__
#define __SCENE_102_H__

#include "cocos2d.h"
class Scene102 : public cocos2d::Scene
{
private:
    cocos2d::Sprite* btn_cuber; // 場景中會放置的按鈕
    cocos2d::Sprite* btn_replay;
    cocos2d::Sprite* btn_return;
    cocos2d::Rect    cuber_rect;
    cocos2d::Rect    replay_rect;
    cocos2d::Rect    return_rect; //包含住按鈕的長方形

    cocos2d::Sprite* bean01;
    cocos2d::Rect    bean01_rect;

    cocos2d::Point pt_cur, pt_old;
    bool _bBean01;

    int _sceneno;
    std::string _strSceneNo;
    cocos2d::Label* labelBMF;

public:
    Scene102();
    ~Scene102();
    static cocos2d::Scene* createScene();  // 回傳值型別是 Scene 的靜態指標
    virtual bool init(); // 這個函式將會在 create() 函式中被呼叫
    void update(float dt);

    bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //觸碰開始事件,回傳值必須是 bool
    void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //觸碰移動事件
    void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent); //觸碰結束事件 

    // implement the "static create()" method manually
    CREATE_FUNC(Scene102); //展開後定義了 create() 成員函式

};

#endif // __SCENE_101_H__
