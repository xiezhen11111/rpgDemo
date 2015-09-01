#include "BaseRole.h"
#include "BaseFSM.h"
#include "BaseAI.h"

BaseRole * BaseRole::createWithProperty( PropertyManager * manager )
{
	BaseRole * baseRole=new BaseRole();

	if (baseRole && baseRole->init(manager))
	{
		baseRole->autorelease();
	}else
	{
		CC_SAFE_DELETE(baseRole);
		return nullptr;
	}

	return baseRole;
}

bool BaseRole::init( PropertyManager * manager )
{
	property=manager;

	//��������
	this->type=static_cast<ROLE_TYPE>(property->getType());

	//���ض�����Դ
	ArmatureDataManager::getInstance()->addArmatureFileInfo(property->getDataName());
	armature=Armature::create(property->getArmatureName());
	armature->getAnimation()->play("default");//defaultΪ���������ڱ༭��������
	this->addChild(armature);

	armature->getAnimation()->setMovementEventCallFunc(
		CC_CALLBACK_0(BaseRole::animationEvent,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));


	return true;

}

Rect BaseRole::getRealRect( BaseRole * role ,Rect rect )
{
	Rect realRect=Rect(rect.origin.x+role->getPositionX(),rect.origin.y+role->getPositionY()
		,rect.size.width,rect.size.height);

	return realRect;

}


void BaseRole::animationEvent( Armature * pArmature,MovementEventType movementType,const std::string & movementIDstr )
{
	const char * movementID=movementIDstr.c_str();


	if (strcmp(movementID,"attack")==0)
	{
		//�ڲ��Ź�������

		if (movementType==START)
		{
			//��������ײ���
			if (lockRole!=nullptr && state!=ROLE_DEAD)
			{
				if (getRealRect(this,property->getHitRect()).intersectsRect(lockRole->getRealRect(lockRole,property->getGetHitRect())))
				{
					log("������");

					int atk=property->getATK();

					__String * hpStr=__String::createWithFormat("%d",atk);
					lockRole->fallHP(hpStr->getCString());

					lockRole->property->setHP(lockRole->property->getHP()-atk);

					if (lockRole->property->getHP()<=0)
					{

						//����
						lockRole->getBaseAI()->stopRoleAI();
						lockRole->getBaseFSM()->changeToDead();

					}
				}

			}

		} 
		else if(movementType==COMPLETE)
		{
			baseFSM->changeToDefault();

		}

	}else if (strcmp(movementID,"gethit")==0)
	{
		//��������

		if (movementType==COMPLETE)
		{
			armature->runAction(Sequence::create(FadeOut::create(0.5),
				CallFunc::create([=](){state=ROLE_FREE;}),NULL));

		}

	}




	
}



void BaseRole::changeFace( ROLE_FACE face )
{

	if (face==FACE_LEFT)
	{
		armature->setScaleX(-1);
		property->setHitRect(Rect(
			-property->getHitPoint().x-property->getHitRect().size.width,
			property->getHitRect().origin.y,
			property->getHitRect().size.width,
			property->getHitRect().size.height
			));

		this->face=face;

	} else if (face==FACE_RIGHT)
	{
		armature->setScaleX(1);
		property->setHitRect(Rect(
			property->getHitPoint().x,
			property->getHitRect().origin.y,
			property->getHitRect().size.width,
			property->getHitRect().size.height
			));

		this->face=face;

	}

}

void BaseRole::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(BaseRole::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void BaseRole::onDraw(const Mat4 &transform, uint32_t flags)
{
	
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	//draw
	CHECK_GL_ERROR_DEBUG();

	//������
	Rect rect=property->getHitRect();
	DrawPrimitives::setDrawColor4B(0,0,255,255);
	DrawPrimitives::drawRect(Vec2(rect.getMinX(),rect.getMinY()),Vec2(rect.getMaxX(),rect.getMaxY()));
//	CCLOG("===onDraw===%f===%f===%f===%f",rect.getMinX(),rect.getMinY(),rect.getMaxX(),rect.getMaxY());
	
	//�ܻ���
	rect=property->getGetHitRect();
	DrawPrimitives::setDrawColor4B(0,255,0,255);
	DrawPrimitives::drawRect(Vec2(rect.getMinX(),rect.getMinY()),Vec2(rect.getMaxX(),rect.getMaxY()));

	CHECK_GL_ERROR_DEBUG();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}

void BaseRole::fallHP( const char * hpCount )
{
	FlyText * flyText=FlyText::create(hpCount);
	flyText->startAnimation();
	this->addChild(flyText);
}

void BaseRole::purge()
{
	this->getBaseFSM()->purge();
	this->getBaseAI()->purge();
	removeFromParent();

}




