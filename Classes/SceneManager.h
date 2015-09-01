#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class SceneManager
{
public:
	Scene * startScene;
	Scene * gameScene;

	void createScene();
	void toGameScene();


};

#endif // __HELLOWORLD_SCENE_H__