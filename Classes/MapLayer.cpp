
#include "MapLayer.h"

void MapLayer::setBackGround( const std::string& filename )
{
	//ע�������ȻҪ�ж��Ƿ��ǿ�ָ���һ��Ҫ�ڹ��캯���г�ʼ��������ᱨ��
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

