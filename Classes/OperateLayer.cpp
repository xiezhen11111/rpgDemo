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
	�ڶ���д������Ҫ�����ص������Ĳ������ͣ����忴Դ��
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

