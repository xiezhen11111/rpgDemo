#ifndef __DIALOG_LAYER_H__
#define __DIALOG_LAYER_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"


USING_NS_CC;
using namespace ui;


class DialogLayer : public cocos2d::Layer
{
public:
	static DialogLayer * createWithJsonFile(const char * filename);

	bool init(std::string str);
	void multUpdate(float dt);
	void getDataByIndex(int index);
	void showAllContent();

private:
	bool _isOver;
	int index;

	std::string conversation;
	std::vector<std::string> _conVector;

	cocos2d::TextFieldTTF * speetch;
	TextFieldTTF * name;

	std::string mStr;
	std::string tempStr;
	std::vector<std::string>strVector;
	int vecLength;

	ImageView * icon;

	//判断中文字符占几个字节
	void pushChineseStr(std::string str,std::vector<std::string> &strVector);

	bool onTouchBegin(Touch * touch ,Event * unused_event);
	void onTouchEnded(Touch * touch ,Event * unused_event);

};

#endif // __HELLOWORLD_SCENE_H__