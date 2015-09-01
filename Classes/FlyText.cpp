#include "FlyText.h"


FlyText * FlyText::create( const char * str )
{
	FlyText * flyText=new FlyText();
	if (flyText && flyText->init(str))
	{
		flyText->autorelease();
	}else
	{
		CC_SAFE_DELETE(flyText);
	}

	return flyText;
}

bool FlyText::init( const char * str )
{
	label=Label::createWithSystemFont(str,"",30);
	label->setColor(Color3B::RED);
	this->addChild(label);

	return true;

}

void FlyText::startAnimation()
{
	auto easeIn=EaseExponentialIn::create(Spawn::create(MoveBy::create(.7f,Vec2(0,150)),FadeOut::create(.7),NULL));

	auto sequence=Sequence::create(easeIn,CallFunc::create([&](){this->removeObject();}),NULL);

	label->runAction(sequence);
}

void FlyText::removeObject()
{
	stopAllActions();
	removeAllChildrenWithCleanup(true);
	this->removeFromParent();
}

