#include "DialogLayer.h"
#include "json/rapidjson.h"
#include "json/document.h"

using namespace rapidjson;

DialogLayer * DialogLayer::createWithJsonFile( const char * filename )
{
	DialogLayer * dialogLayer=new DialogLayer();

	if (dialogLayer && dialogLayer->init(filename))
	{
		dialogLayer->autorelease();
	} 
	else
	{
		CC_SAFE_DELETE(dialogLayer);

	}

	return dialogLayer;

}

bool DialogLayer::init( std::string str )
{
	//初始化界面

	//背景
	Size size=Size(Director::getInstance()->getVisibleSize().width,Director::getInstance()->getVisibleSize().height);
	Layout * layout=Layout::create();
	layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
	layout->setColor(Color3B::BLACK);
	layout->setOpacity(180);
	layout->setSize(size);
	//layout->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(layout);

	//头像框
	icon=ImageView::create();
	icon->setPosition(Vec2(300,200));
	icon->ignoreContentAdaptWithSize(true);
	this->addChild(icon);

	//文本框
	name=TextFieldTTF::textFieldWithPlaceHolder("Please Click Me!", "", 24);
	name->setColor(Color3B::GREEN);
	name->setPosition(Vec2(400,150));
	this->addChild(name);

	speetch =TextFieldTTF::textFieldWithPlaceHolder("Please Click Me!", "", 24);
	speetch->setColor(Color3B::RED);
	speetch->setPosition(Vec2(400,50));
	this->addChild(speetch);


	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);//吞噬,这样在显示的时候后面的按钮就不会接受事件
	touchListener->onTouchBegan=CC_CALLBACK_2(DialogLayer::onTouchBegin,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(DialogLayer::onTouchEnded,this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);


	conversation=FileUtils::getInstance()->getStringFromFile(str);

	index=0;
	getDataByIndex(index);


	return true;

}

void DialogLayer::multUpdate( float dt )
{
	if (vecLength<(int)strVector.size())
	{
		tempStr=tempStr+strVector[vecLength].c_str();
		speetch->setString(tempStr.c_str());
		vecLength++;
	} 
	else
	{
		_isOver=true;
		unschedule(schedule_selector(DialogLayer::multUpdate));
	}
}

void DialogLayer::getDataByIndex( int index )
{
	Document doc;
	doc.Parse<kParseDefaultFlags>(conversation.c_str());
	_conVector.clear();//会调用很多次，所以先clear下
	_isOver=false;
	vecLength=0;
	rapidjson::Value & array=doc["Conversation"];


	if (array.IsArray())
	{
		int i=index;
		int j=0;
		strVector.clear();

		if (i>=array.Size())
		{
			//全部说完了，移除对话框
			this->removeFromParent();
			return;
		}

		for (j=0;j<array[i]["content"].Size();j++)
		{
			rapidjson::Value & str=array[i]["content"][j];
			mStr=str.GetString();
			log("test str %s ",mStr);
			_conVector.push_back(str.GetString());

			if (j==2)
			{
				pushChineseStr(mStr,strVector);
			}
		}

		name->setString(_conVector[0]);
		icon->loadTexture(_conVector[1]);
	}

	tempStr="";
	schedule(CC_SCHEDULE_SELECTOR(DialogLayer::multUpdate),.1f);

}

void DialogLayer::showAllContent()
{
	_isOver=true;
	unschedule(schedule_selector(DialogLayer::multUpdate));
	speetch->setString(mStr.c_str());
}

void DialogLayer::pushChineseStr( std::string str,std::vector<std::string> &strVector )
{
	int sum=strlen(str.c_str());

	for (int cur=0;cur<sum;cur++)
	{
		std::string lines;
		char t=str[cur];

		if ((t & 0xe0)==0xe0)//1110 0000 3 byte
		{
			lines=lines +t +str[cur+1]+str[cur+2];
			cur+=3;

		} 
		else if ((t & 0xc0)==0xc0)//2 byte
		{
			lines=lines +t +str[cur+1];
			cur+=2;
		}else
		{
			lines=lines +t;
			cur++;
		}
		log("streaming text : %s",lines.c_str());
		strVector.push_back(lines);
	}
}

void DialogLayer::onTouchEnded( Touch * touch ,Event * unused_event )
{
	log("===========onTouchEnded============");

	if (_isOver)
	{
		//播完了播放下一个
		index++;
		getDataByIndex(index);

	} 
	else
	{
		//马上显示全部
		this->showAllContent();
	}
}

bool DialogLayer::onTouchBegin( Touch * touch ,Event * unused_event )
{
	return true;

}

