
#include "MapLayer.h"

void MapLayer::setBackGround( const std::string& filename )
{
	//注意这里既然要判断是否是空指针就一定要在构造函数中初始化，否则会报错
	if (backImageView==nullptr)
	{
		backImageView=ImageView::create();
		backImageView->setAnchorPoint(Point::ZERO);
		backImageView->setPosition(Point::ZERO);
		this->addChild(backImageView);

	}

	backImageView->loadTexture(filename);
	


}

bool MapLayer::init()
{
	

	return true;
}

MapLayer::MapLayer()
{
	backImageView=nullptr;
}

