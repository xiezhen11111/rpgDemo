#ifndef __PROPERT_MANAGER_H__
#define __PROPERT_MANAGER_H__

#include "cocos2d.h"


USING_NS_CC;


/**
 * ��ɫ���ԵĹ���
 * 
 * 
*/	
class PropertyManager : public Ref
{

public:
	CREATE_FUNC(PropertyManager);
	virtual bool init();

public :

	CC_SYNTHESIZE(int ,ID,ID);
	CC_SYNTHESIZE(int ,HP,HP);
	CC_SYNTHESIZE(int ,ATK,ATK);
	CC_SYNTHESIZE(int ,Speed,Speed);
	CC_SYNTHESIZE(int ,Type,Type);

	//����������Ұ��
	CC_SYNTHESIZE(unsigned int ,LockLimit,LockLimit);

	//��������
	CC_SYNTHESIZE(unsigned int ,ATKLimit,ATKLimit);

	CC_SYNTHESIZE(std::string ,ArmatureName,ArmatureName);
	CC_SYNTHESIZE(std::string ,DataName,DataName);
	CC_SYNTHESIZE(std::string ,PlayerName,PlayerName);

	CC_SYNTHESIZE(Rect ,HitRect,HitRect);
	CC_SYNTHESIZE(Point ,HitPoint,HitPoint);

	CC_SYNTHESIZE(Rect ,GetHitRect,GetHitRect);
	CC_SYNTHESIZE(Point ,GetHitPoint,GetHitPoint);



};

#endif // __HELLOWORLD_SCENE_H__