#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"
#include <iostream>
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class MapLayer:public Layer
{
public:
	CREATE_FUNC(MapLayer);
	virtual bool init();

	MapLayer();

	//°ó¶¨±³¾°Í¼Æ¬
	void setBackGround(const std::string& filename);

public:
	ImageView * backImageView;



};

#endif // __HELLOWORLD_SCENE_H__