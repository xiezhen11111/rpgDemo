#ifndef __FLY_TEXT_H__
#define __FLY_TEXT_H__

#include "cocos2d.h"

USING_NS_CC;

class FlyText:public Node
{
public:
	static FlyText * create(const char * str);

	bool init(const char * str);
	void startAnimation();
	void removeObject();

private:
	Label * label;



};

#endif // __HELLOWORLD_SCENE_H__