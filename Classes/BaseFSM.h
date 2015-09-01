#ifndef __BASE_FSM_H__
#define __BASE_FSM_H__

#include "cocos2d.h"


USING_NS_CC;

class BaseRole;

/**
 * 
 * 状态机
 * 
*/	
class BaseFSM:public Ref
{
public:
	static BaseFSM * createFSM(BaseRole * baseRole);
	bool init(BaseRole * baseRole);
 
	void switchMoveState(int dir);
	void changeToDefault();
	void changeToAttack();
	void changeToLeft();
	void changeToRight();
	void changeToDead();
	void changeToEnemy();//移向敌人（相对的敌人） 用于AI
	void purge();

	BaseRole * role;

};

#endif // __HELLOWORLD_SCENE_H__