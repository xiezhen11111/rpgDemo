
#include "SceneManager.h"
#include "MenuLayer.h"
#include "ControlLayer.h"

void SceneManager::createScene()
{
	startScene=Scene::create();
	auto menuLayer=MenuLayer::create();
	menuLayer->tsm=this;
	startScene->addChild(menuLayer);

}

void SceneManager::toGameScene()
{
	gameScene=Scene::create();
	ControlLayer * controlLayer=ControlLayer::create();
	controlLayer->tsm=this;
	gameScene->addChild(controlLayer);
	Director::getInstance()->replaceScene(gameScene);

}

