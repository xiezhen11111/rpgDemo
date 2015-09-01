#include "BaseFSM.h"
#include "BaseRole.h"

BaseFSM * BaseFSM::createFSM( BaseRole * baseRole )
{
	BaseFSM * baseFSM=new BaseFSM();
	if (baseFSM && baseFSM->init(baseRole))
	{
		baseFSM->autorelease();
	}else
	{
		CC_SAFE_DELETE(baseFSM);
	}

	return baseFSM;


}

bool BaseFSM::init( BaseRole * baseRole )
{

	role=baseRole;

	return true;

}

void BaseFSM::switchMoveState( int dir )
{

	if (role->state ==ROLE_ATTACK)
	{
		//不要打断攻击状态
		return;
	}

	switch (dir)
	{

	case  0:
		this->changeToDefault();

		break;

	case  1:
		this->changeToRight();
		break;

	case  3:
		this->changeToLeft();
		break;

	default:
		role->getArmature()->stopAllActions();
		break;
	}




}

void BaseFSM::changeToDefault()
{
	if (role->state!=ROLE_DEFAULT && role->state!=ROLE_DEAD)
	{
		role->state=ROLE_DEFAULT;
		role->getArmature()->getAnimation()->play("default");
	}
}

void BaseFSM::changeToAttack()
{
	if (role->state!=ROLE_ATTACK && role->state!=ROLE_DEAD)
	{
		role->state=ROLE_ATTACK;
		role->getArmature()->getAnimation()->play("attack",-1,0);//不循环播放
	}
}

void BaseFSM::changeToLeft()
{
	if (role->state!=ROLE_MOVE && role->state!=ROLE_DEAD)
	{
		role->state=ROLE_MOVE;
	}

	/*人朝左 脸朝右 播放的应该是倒退动画*/
	if (role->face==FACE_RIGHT)
	{
		std::string movent =role->getArmature()->getAnimation()->getCurrentMovementID();
		char * nowMovent=const_cast<char *>(movent.c_str());
		if (strcmp(nowMovent,"run_back")!=0)
		{
			role->getArmature()->getAnimation()->play("run_back");
		}

	}else
	{
		std::string movent =role->getArmature()->getAnimation()->getCurrentMovementID();
		char * nowMovent=const_cast<char *>(movent.c_str());
		if (strcmp(nowMovent,"run_front")!=0)
		{
			role->getArmature()->getAnimation()->play("run_front");
		}
	}


	role->setPosition(Vec2(role->getPositionX()-role->property->getSpeed(),
		role->getPositionY()));
}

void BaseFSM::changeToRight()
{


	if (role->state!=ROLE_MOVE && role->state!=ROLE_DEAD)
	{
		role->state=ROLE_MOVE;
	}

	/*人朝右 脸朝右 播放的应该是前进动画*/
	if (role->face==FACE_RIGHT)
	{
		std::string movent =role->getArmature()->getAnimation()->getCurrentMovementID();
		char * nowMovent=const_cast<char *>(movent.c_str());
		if (strcmp(nowMovent,"run_front")!=0)
		{
			role->getArmature()->getAnimation()->play("run_front");
		}

	}else
	{
		std::string movent =role->getArmature()->getAnimation()->getCurrentMovementID();
		char * nowMovent=const_cast<char *>(movent.c_str());
		if (strcmp(nowMovent,"run_back")!=0)
		{
			role->getArmature()->getAnimation()->play("run_back");
		}
	}


	role->setPosition(Vec2(role->getPositionX()+role->property->getSpeed(),
		role->getPositionY()));

}

void BaseFSM::changeToDead()
{
	if ( role->state!=ROLE_DEAD)
	{
		role->state=ROLE_DEAD;
		role->getArmature()->getAnimation()->play("gethit",-1,0);//不循环播放
	}
}

void BaseFSM::changeToEnemy()
{

}

void BaseFSM::purge()
{
	role=nullptr;
	CC_SAFE_RELEASE(this);

}

