#ifndef __BASE_ROLE_H__
#define __BASE_ROLE_H__

#include "cocos2d.h"
#include "PropertyManager.h"
#include "cocostudio/CocoStudio.h"
#include "FlyText.h"

USING_NS_CC;
using namespace cocostudio;

//��ɫ����
typedef enum
{
	TYPE_HERO=1,
	TYPE_MONSTER=2,

}ROLE_TYPE;

//��ɫ��״̬
typedef enum
{
	ROLE_DEFAULT=1,
	ROLE_ATTACK,
	ROLE_MOVE,
	ROLE_DEAD,
	ROLE_FREE,//��ɫ���ڸ�״̬ʱ�ᱻ�ͷŵ�

}ROLE_STATE;

//��ɫ���ĳ���
typedef enum
{
	FACE_LEFT,
	FACE_RIGHT,

}ROLE_FACE;

class BaseFSM;
class BaseAI;

class BaseRole : public Node
{
public:
	static BaseRole * createWithProperty(PropertyManager * manager);

	bool init(PropertyManager * manager);

public:
	BaseRole * lockRole;//���ж���
	PropertyManager * property;
	ROLE_TYPE type;
	ROLE_STATE state;
	ROLE_FACE face;
	CC_SYNTHESIZE(Armature *,armature,Armature);
	/*
	������������ͷ�ļ������г������ظ����ã�BaseRole��BaseFSM��������Ī������Ĵ���
	����������ǣ������ֻ����������һ�����ж���һ����ĳ�Ա������ֻҪ��ͷ�ļ���
	���� 
		class ����;
	Ȼ��Ҫ��.cpp�ļ��а������ͷ�ļ��Ϳ�����
	֮���Է����������������Ϊ��ʾ����������ʵ��û�д���˵���������BaseFSM�����⣬�ͷ�����ͷ�ļ��������ظ�����

	�����������������ʹ�ÿ��Բ�����ͷ�ļ�����class �������ɣ���ʹ������Ķ��壨���ԣ�������ʱ�ڵ���ͷ�ļ�,�������ִ��󣺲�����ָ��ָ��������������
	*/
	CC_SYNTHESIZE(BaseFSM *,baseFSM,BaseFSM);
	CC_SYNTHESIZE(BaseAI *,baseAI,BaseAI);
	//�ı䳯��
	void changeFace(ROLE_FACE face);
	
	//�����Ļص�����
	void animationEvent(Armature * pArmature,MovementEventType movementType,const std::string & movementIDstr);

	//������ײ�ľ���
	Rect getRealRect(BaseRole * role ,Rect rect);

	//��Ѫ
	void fallHP(const char * hpCount);
	
	//�ͷŶ���
	void purge();

	//���ƺ���
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
};

#endif // __HELLOWORLD_SCENE_H__