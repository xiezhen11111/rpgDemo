#include "BaseAI.h"
#include "BaseRole.h"
#include "RoleCardController.h"
#include "BaseFSM.h"

BaseAI * BaseAI::createAI( BaseRole * baseRole )
{
	BaseAI * ai=new BaseAI();
	if (ai && ai->init(baseRole))
	{
		ai->autorelease();
	}else
	{
		CC_SAFE_DELETE(ai);
	}

	return ai;
}

bool BaseAI::init( BaseRole * role )
{
	baseRole=role;

	return  true;

}

void BaseAI::startRoleAI()
{
	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(BaseAI::updateFunc),this,(float)1/60,false);
}

void BaseAI::stopRoleAI()
{
	Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(BaseAI::updateFunc),this);
}

void BaseAI::updateFunc( float dt )
{

	//相对来说的敌人
	std::vector<BaseRole *>roleVec;
	if (baseRole->type==TYPE_HERO)
	{
		roleVec=RoleCardController::getInstance()->monsterVec;
	} 
	else if (baseRole->type==TYPE_MONSTER)
	{
		roleVec=RoleCardController::getInstance()->heroVec;
	}

	//记录距离当前人物最近的角色编号
	int roleID=0;
	if (roleVec.size()!=0)
	{
		float distance=Director::getInstance()->getVisibleSize().width;

		for (int i=0;i<roleVec.size();i++)
		{
			float newDis=abs(baseRole->getPosition().distance(roleVec[i]->getPosition()));

			if (newDis<distance)
			{
				roleID=i;
				distance=newDis;
			}

		}

		if (roleVec[roleID]->getPositionX()>baseRole->getPositionX())
		{
			baseRole->changeFace(FACE_RIGHT);
		} 
		else
		{
			baseRole->changeFace(FACE_LEFT);
		}


	}else
	{
		//为空

		//无对象了将锁敌对象置空
		baseRole->lockRole=nullptr;
		return;
	}

	//设置锁敌对象
	baseRole->lockRole=roleVec[roleID];



	//针对monster的
	if (baseRole->type==TYPE_MONSTER)
	{
		Vec2 enemyPos=roleVec[roleID]->getPosition();

		if (baseRole->getPosition().distance(enemyPos)<baseRole->property->getLockLimit())
		{
			if (baseRole->getPosition().distance(enemyPos)<baseRole->property->getATKLimit())
			{
				//攻击

				baseRole->getBaseFSM()->changeToAttack();
			} 
			else
			{
				//移动
				//判断移动方向
				if (baseRole->face==FACE_LEFT && baseRole->state!=ROLE_ATTACK)
				{
					baseRole->getBaseFSM()->changeToLeft();
				} 
				else if (baseRole->face==FACE_RIGHT && baseRole->state!=ROLE_ATTACK)
				{
					baseRole->getBaseFSM()->changeToRight();

				}

			}

		}else
		{
			baseRole->getBaseFSM()->changeToDefault();
		}


	}

}

void BaseAI::purge()
{
	stopRoleAI();
	baseRole=nullptr;
	CC_SAFE_RELEASE(this);

}

