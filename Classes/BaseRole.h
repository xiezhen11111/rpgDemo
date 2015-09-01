#ifndef __BASE_ROLE_H__
#define __BASE_ROLE_H__

#include "cocos2d.h"
#include "PropertyManager.h"
#include "cocostudio/CocoStudio.h"
#include "FlyText.h"

USING_NS_CC;
using namespace cocostudio;

//角色类型
typedef enum
{
	TYPE_HERO=1,
	TYPE_MONSTER=2,

}ROLE_TYPE;

//角色的状态
typedef enum
{
	ROLE_DEFAULT=1,
	ROLE_ATTACK,
	ROLE_MOVE,
	ROLE_DEAD,
	ROLE_FREE,//角色处于该状态时会被释放掉

}ROLE_STATE;

//角色脸的朝向
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
	BaseRole * lockRole;//锁敌对象
	PropertyManager * property;
	ROLE_TYPE type;
	ROLE_STATE state;
	ROLE_FACE face;
	CC_SYNTHESIZE(Armature *,armature,Armature);
	/*
	插曲：由于在头文件引用中出现了重复引用（BaseRole与BaseFSM）导致了莫名其妙的错误，
	解决方法就是：如果你只是想在另外一个类中定义一个类的成员变量，只要在头文件中
	加入 
		class 类名;
	然后要在.cpp文件中包含这个头文件就可以了
	之所以发现是这个问题是因为提示这句出错，但是实际没有错误，说明可能这个BaseFSM有问题，就发现了头文件出现了重复引用

	如果仅仅是声明类型使用可以不导入头文件而是class 类名即可，在使用里面的定义（属性，方法）时在导入头文件,否则会出现错误：不允许指针指向不完整的类类型
	*/
	CC_SYNTHESIZE(BaseFSM *,baseFSM,BaseFSM);
	CC_SYNTHESIZE(BaseAI *,baseAI,BaseAI);
	//改变朝向
	void changeFace(ROLE_FACE face);
	
	//动画的回调函数
	void animationEvent(Armature * pArmature,MovementEventType movementType,const std::string & movementIDstr);

	//真正碰撞的矩形
	Rect getRealRect(BaseRole * role ,Rect rect);

	//掉血
	void fallHP(const char * hpCount);
	
	//释放对象
	void purge();

	//绘制函数
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
};

#endif // __HELLOWORLD_SCENE_H__