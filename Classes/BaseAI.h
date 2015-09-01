#ifndef __BASE_AI_H__
#define __BASE_AI_H__

#include "cocos2d.h"


USING_NS_CC;

class BaseRole;

/**
 * 
 * ״̬��
 * 
*/	
class BaseAI:public Ref
{
public:
	static BaseAI * createAI(BaseRole * baseRole);

	bool init(BaseRole * role);
	void startRoleAI();
	void stopRoleAI();//����ʱ������
	void updateFunc(float dt);
	void purge();//�ͷ�

	BaseRole * baseRole;

};

#endif // __HELLOWORLD_SCENE_H__