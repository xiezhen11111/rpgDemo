#ifndef __OPERATE_LAYER_H__
#define __OPERATE_LAYER_H__

#include "cocos2d.h"
#include <iostream>
#include "SceneManager.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class OperateLayer:public Layer
{
public:
	CREATE_FUNC(OperateLayer);
	virtual bool init();
	void  touchCallBack(Ref* ref,TouchEventType t);

public:
	SceneManager * tsm;



};

#endif // __HELLOWORLD_SCENE_H__