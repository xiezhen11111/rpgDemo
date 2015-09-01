#include "RoleCardController.h"

static RoleCardController * roleCardController=nullptr;

RoleCardController * RoleCardController::getInstance()
{
	if (roleCardController==nullptr)
	{
		roleCardController=new (std::nothrow)RoleCardController();
		roleCardController->init();
	}

	return roleCardController;

}

bool RoleCardController::init()
{


	return true;

}

BaseRole * RoleCardController::getHero()
{
	for(int i=0;i<heroVec.size();i++)
	{
		if (heroVec[i]->property->getID()==this->getHeroID())
		{
			return heroVec[i];
		}

	}


	return nullptr;

}

void RoleCardController::purge()
{
	if (heroVec.size()!=0)
	{
		for (int i=0;i<heroVec.size();i++)
		{
			heroVec[i]->purge();
		}
	}

	if (monsterVec.size()!=0)
	{
		for (int i=0;i<monsterVec.size();i++)
		{
			monsterVec[i]->purge();
		}
	}


	heroVec.clear();
	heroVec.shrink_to_fit();
	monsterVec.clear();
	monsterVec.shrink_to_fit();

}

