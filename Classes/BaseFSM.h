#ifndef __BASE_FSM_H__
#define __BASE_FSM_H__

#include "cocos2d.h"


USING_NS_CC;

class BaseRole;

/**
 * 
 * ״̬��
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
	void changeToEnemy();//������ˣ���Եĵ��ˣ� ����AI
	void purge();

	BaseRole * role;

};

#endif // __HELLOWORLD_SCENE_H__