
#include "HRocker.h"

#define  PI 3.1415926

HRocker * HRocker::createHRocker( const char * rockerImgName, const char * rockerBGImageName,Vec2 position )
{
	HRocker * layer=HRocker::create();

	if(layer)
	{
		layer->rockerInit(rockerImgName,rockerBGImageName,position);

		return layer;
	}


	CC_SAFE_DELETE(layer);

	return nullptr;


}

void HRocker::startRocker( bool _isStopOther )
{
	auto rocker=(Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	auto rockerBG=(Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);

	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);//������
	touchListener->onTouchBegan=CC_CALLBACK_2(HRocker::onTouchBegin,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(HRocker::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(HRocker::onTouchEnded,this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
}

void HRocker::stopRocker()
{
	auto rocker=(Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	auto rockerBG=(Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	

}

void HRocker::rockerInit(const char * rockerImgName,
						 const char * rockerBGImageName,Vec2 position)
{
	auto spRockerBG=Sprite::create(rockerBGImageName);
	spRockerBG->setPosition(position);
	spRockerBG->setVisible(false);
	this->addChild(spRockerBG,0,tag_rockerBG);


	auto spRocker=Sprite::create(rockerImgName);
	spRocker->setPosition(position);
	spRocker->setVisible(false);
	this->addChild(spRocker,0,tag_rocker);

	rockerBGPosition=position;
	rockerBGR=spRockerBG->getContentSize().width/2;
	rockerDirection=-1;
	isCanMove=false;

}



bool HRocker::onTouchBegin( Touch * touch ,Event * unused_event )
{
	//��ȡ��Ļ�ϵĴ���������

	Vec2 point =touch->getLocation();
	auto rocker=(Sprite *)this->getChildByTag(tag_rocker);

	if (rocker->getBoundingBox().containsPoint(point))
	{
		isCanMove=true;
		log("begin");
	}

	return true;

}

void HRocker::onTouchMoved( Touch * touch ,Event * unused_event )
{
	if (!isCanMove)
	{
		return;
	}

	Vec2 point =touch->getLocation();
	auto rocker=(Sprite *)this->getChildByTag(tag_rocker);

	//����ҡ���봥�����γɵĽǶ�
	float angle=getRad(rockerBGPosition,point);

	if (sqrt(pow(rockerBGPosition.x-point.x,2)+pow(rockerBGPosition.y-point.y,2))>=rockerBGR)
	{
		//��ָ�Ƴ��˱���֮��
		rocker->setPosition(ccpAdd(getAnglePosition(rockerBGR,angle),rockerBGPosition));

	}else
	{
		//��ҡ�˱�����
		rocker->setPosition(point);
	}


	//����ҡ�˷���
	if (angle>=-PI/4 && angle <PI/4)
	{
		rockerDirection=rocker_right;
		rockerRun=false;

	}else if (angle>=PI/4 && angle <3*PI/4)
	{
		rockerDirection=rocker_up;

	}else if ((angle>=3*PI/4 && angle<=PI) || (angle <-3*PI/4  && angle>=-PI))
	{
		rockerDirection=rocker_left;
		rockerRun=true;

	}else if (angle>=-3*PI/4 && angle <-PI/4)
	{
		rockerDirection=rocker_down;
	}
	

	
}

void HRocker::onTouchEnded( Touch * touch ,Event * unused_event )
{
	if (!isCanMove)
	{
		return;
	}

	auto rocker=(Sprite *)this->getChildByTag(tag_rocker);
	rocker->stopAllActions();
	rocker->runAction(MoveTo::create(0.08f,rockerBGPosition));//�ص�ԭ����λ��
	isCanMove=false;
	rockerDirection=rocker_stay;



}

float HRocker::getRad( Vec2 pos1,Vec2 pos2 )
{
	float px1=pos1.x;
	float py1=pos1.y;
	float px2=pos2.x;
	float py2=pos2.y;

	float x=px2-px1;
	float y=py2-py1;

	float xie= sqrt(pow(x,2)+pow(y,2));
	float cosAngle=x/xie;//�������ֵ
	float rad =acos(cosAngle);//����������Ƕ�

	//����������y����С��ҡ�˵�y���꣨�����������ޣ�����Ҫ���õ��Ľ��ȡ��
	if (py2<py1)
	{
		rad=-rad;
	}


	return rad;


}

Vec2 HRocker::getAnglePosition( float r,float angle )
{
	return Vec2(r*cos(angle),r*sin(angle));
}
