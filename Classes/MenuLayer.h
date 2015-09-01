#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include <iostream>
#include "SceneManager.h"

USING_NS_CC;

class MenuLayer:public Layer
{
public:
	CREATE_FUNC(MenuLayer);
	virtual bool init();
	 void menuStartCallback(cocos2d::Ref* pSender);

public:
	SceneManager * tsm;



};

#endif // __HELLOWORLD_SCENE_H__