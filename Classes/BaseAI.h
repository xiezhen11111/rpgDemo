#ifndef __BASE_AI_H__
#define __BASE_AI_H__

#include "cocos2d.h"


USING_NS_CC;

class BaseRole;

/**
 * 
 * 状态机
 * 
*/	
class BaseAI:public Ref
{
public:
	static BaseAI * createAI(BaseRole * baseRole);

	bool init(BaseRole * role);
	void startRoleAI();
	void stopRoleAI();//挂了时候会调用
	void updateFunc(float dt);
	void purge();//释放

	BaseRole * baseRole;

};

#endif // __HELLOWORLD_SCENE_H__