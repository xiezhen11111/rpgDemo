
#include "MenuLayer.h"
#include "ui/CocosGUI.h"

bool MenuLayer::init()
{

	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CCLOG("----%f----%f----",visibleSize.width,visibleSize.height);//960 640
	/*CCLOG("==============");
	log("-----------");*/
	auto closeItem = MenuItemImage::create(
		"start.png",
		"",
		CC_CALLBACK_1(MenuLayer::menuStartCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto sprite = Sprite::create("bg.jpg");
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	this->addChild(sprite, 0);

	/*auto backImageView=ui::ImageView::create("bg.jpg");
	this->addChild(backImageView);*/
	return true;

}

void MenuLayer::menuStartCallback( cocos2d::Ref* pSender )
{
	this->tsm->toGameScene();
}

