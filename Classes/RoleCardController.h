#ifndef __ROLECARD_CONTROLLER_H__
#define __ROLECARD_CONTROLLER_H__

#include "cocos2d.h"
#include "BaseRole.h"

USING_NS_CC;

/**
 * 
 *角色管理类
 * 
*/	
class RoleCardController:public Ref
{
public:

	static RoleCardController * getInstance();
	bool init();

public:
	std::vector<BaseRole *>heroVec;
	std::vector<BaseRole *>monsterVec;

	BaseRole * getHero();
	void purge();

public:
	CC_SYNTHESIZE(int ,HeroID,HeroID);

};

#endif // __HELLOWORLD_SCENE_H__