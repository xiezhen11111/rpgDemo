#include "OperateLayer.h"
#include "RoleCardController.h"
#include "BaseFSM.h"

bool OperateLayer::init()
{

	if (!Layer::init())
	{
		return  false;
	}


	Button * button =Button::create();
	button->loadTextures("start.png","");
	button->setPosition(Vec2(800,200));
	button->addTouchEventListener(this,toucheventselector(OperateLayer::touchCallBack));
	/*
	第二种写法：需要调整回调函数的参数类型，具体看源码
	*button->addTouchEventListener(CC_CALLBACK_2(OperateLayer::touchCallBack,this));
	*/
	this->addChild(button);


	return true; 

}

void OperateLayer::touchCallBack(Ref* ref,TouchEventType t )
{
	if (t==TouchEventType::TOUCH_EVENT_ENDED)
	{
	//	auto button =static_cast<Button *>(ref);
		CCLOG("on touch");

		RoleCardController::getInstance()->getHero()->getBaseFSM()->changeToAttack();

	}

}

