#ifndef __CONTROL_LAYER_H__
#define __CONTROL_LAYER_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "HRocker.h"
#include "BaseRole.h"

USING_NS_CC;

class ControlLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(ControlLayer);
	void purge();

public:
	SceneManager * tsm;
	BaseRole * hero;
	HRocker * rocker;
};

#endif // __HELLOWORLD_SCENE_H__