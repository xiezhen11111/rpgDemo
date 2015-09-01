#include "ControlLayer.h"
#include "MapLayer.h"
#include "OperateLayer.h"
#include "PropertyManager.h"
#include <tinyxml2/tinyxml2.h>
#include <json/reader.h>
#include <json/document.h>
#include "RoleCardController.h"
#include "BaseFSM.h"
#include "BaseAI.h"
#include "DataManager.h"
#include "DialogLayer.h"


bool ControlLayer::init()
{
	for (int i = 0; i < DataManager::getInstance()->getLevelDataArrayByIndex
		(DataManager::getInstance()->getLevelIndex()).size(); i++)
	{
		//��ȡxml�ļ�
		PropertyManager * pManager=PropertyManager::create();

		auto doc = new tinyxml2::XMLDocument();
		doc->Parse(FileUtils::getInstance()->getStringFromFile(DataManager::getInstance()->_levelDataArray[i]).c_str());
		auto root = doc->RootElement();

		for (auto e = root->FirstChildElement(); e; e=e->NextSiblingElement()) {

			std::string str;
			str=e->Attribute("ID");
			/*for (auto attr = e->FirstAttribute(); attr; attr=attr->Next()) {
				str+=attr->Name();
				str+=":";
				str+=attr->Value();
				str+=",";
			}*/

			pManager->setID(std::atoi(e->Attribute("ID")));//ע����ô���ַ���ת��Ϊ����
			pManager->setHP(std::atoi(e->Attribute("HP")));
			pManager->setATK(std::atoi(e->Attribute("ATK")));
			pManager->setSpeed(std::atoi(e->Attribute("Speed")));
			pManager->setLockLimit(std::atoi(e->Attribute("LockLimit")));
			pManager->setATKLimit(std::atoi(e->Attribute("ATKLimit")));
			pManager->setType(std::atoi(e->Attribute("Type")));

			pManager->setArmatureName(e->Attribute("ArmatureName"));
			pManager->setDataName(e->Attribute("DataName"));
			pManager->setPlayerName(e->Attribute("PlayerName"));

			pManager->setHitRect(RectFromString(e->Attribute("HitRect")));//ת��Ϊ���ζ���
			pManager->setHitPoint(pManager->getHitRect().origin);
			pManager->setGetHitRect(RectFromString(e->Attribute("GetHitRect")));
			pManager->setGetHitPoint(pManager->getGetHitRect().origin);

			/*int a=std::atoi(e->Attribute("ID"));
			log("%d",a);
			log("%s",str.c_str());*/
		}

		pManager->retain();//��ֹ���ͷţ��о����ü���

		//��ʾ����
		hero=BaseRole::createWithProperty(pManager);
		hero->setPosition(Vec2(200,200));
		hero->face=FACE_RIGHT;
		this->addChild(hero,1,1);

		if (hero->type==TYPE_MONSTER)
		{
			RoleCardController::getInstance()->monsterVec.push_back(hero);
			hero->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*.8,
				Director::getInstance()->getVisibleSize().height*.4));
		} 
		else
		{
			RoleCardController::getInstance()->heroVec.push_back(hero);
			hero->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*.2,
				Director::getInstance()->getVisibleSize().height*.4));

		}

		

		BaseAI * ai=BaseAI::createAI(hero);
		ai->retain();
		ai->startRoleAI();
		hero->setBaseAI(ai);


		BaseFSM * baseFSM=BaseFSM::createFSM(hero);
		baseFSM->retain();
		hero->setBaseFSM(baseFSM);


	}

	//**********************************************************************************************************************************************
	/*if ( !Layer::init() )
	{
	return false;
	}
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto sprite = Sprite::create("battleBg.jpg");
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setScale(3);
	this->addChild(sprite, 0);*/
	
	//��ȡxml�ļ�
	//PropertyManager * pManager=PropertyManager::create();

	//auto doc = new tinyxml2::XMLDocument();
	//doc->Parse(FileUtils::getInstance()->getStringFromFile("hero.xml").c_str());
	//auto root = doc->RootElement();

	//for (auto e = root->FirstChildElement(); e; e=e->NextSiblingElement()) {

	//	std::string str;
	//	str=e->Attribute("ID");
	//	/*for (auto attr = e->FirstAttribute(); attr; attr=attr->Next()) {
	//		str+=attr->Name();
	//		str+=":";
	//		str+=attr->Value();
	//		str+=",";
	//	}*/

	//	pManager->setID(std::atoi(e->Attribute("ID")));//ע����ô���ַ���ת��Ϊ����
	//	pManager->setHP(std::atoi(e->Attribute("HP")));
	//	pManager->setATK(std::atoi(e->Attribute("ATK")));
	//	pManager->setSpeed(std::atoi(e->Attribute("Speed")));
	//	pManager->setLockLimit(std::atoi(e->Attribute("LockLimit")));
	//	pManager->setATKLimit(std::atoi(e->Attribute("ATKLimit")));
	//	pManager->setType(std::atoi(e->Attribute("Type")));

	//	pManager->setArmatureName(e->Attribute("ArmatureName"));
	//	pManager->setDataName(e->Attribute("DataName"));
	//	pManager->setPlayerName(e->Attribute("PlayerName"));

	//	pManager->setHitRect(RectFromString(e->Attribute("HitRect")));//ת��Ϊ���ζ���
	//	pManager->setHitPoint(pManager->getHitRect().origin);
	//	pManager->setGetHitRect(RectFromString(e->Attribute("GetHitRect")));
	//	pManager->setGetHitPoint(pManager->getGetHitRect().origin);

	//	/*int a=std::atoi(e->Attribute("ID"));
	//	log("%d",a);
	//	log("%s",str.c_str());*/
	//}

	//pManager->retain();//��ֹ���ͷţ��о����ü���

	////��ʾ����
	//hero=BaseRole::createWithProperty(pManager);
	//hero->setPosition(Vec2(200,200));
	//hero->face=FACE_RIGHT;
	//this->addChild(hero,1,1);

	//RoleCardController::getInstance()->heroVec.push_back(hero);



	////��ӹ���

	//PropertyManager * mManager=PropertyManager::create();

	//auto doc2 = new tinyxml2::XMLDocument();
	//doc2->Parse(FileUtils::getInstance()->getStringFromFile("monster.xml").c_str());
	//auto root2 = doc2->RootElement();

	//for (auto e = root2->FirstChildElement(); e; e=e->NextSiblingElement()) {

	//	std::string str;
	//	str=e->Attribute("ID");
	//	/*for (auto attr = e->FirstAttribute(); attr; attr=attr->Next()) {
	//		str+=attr->Name();
	//		str+=":";
	//		str+=attr->Value();
	//		str+=",";
	//	}*/

	//	mManager->setID(std::atoi(e->Attribute("ID")));//ע����ô���ַ���ת��Ϊ����
	//	mManager->setHP(std::atoi(e->Attribute("HP")));
	//	mManager->setATK(std::atoi(e->Attribute("ATK")));
	//	mManager->setSpeed(std::atoi(e->Attribute("Speed")));
	//	mManager->setLockLimit(std::atoi(e->Attribute("LockLimit")));
	//	mManager->setATKLimit(std::atoi(e->Attribute("ATKLimit")));
	//	mManager->setType(std::atoi(e->Attribute("Type")));

	//	mManager->setArmatureName(e->Attribute("ArmatureName"));
	//	mManager->setDataName(e->Attribute("DataName"));
	//	mManager->setPlayerName(e->Attribute("PlayerName"));

	//	mManager->setHitRect(RectFromString(e->Attribute("HitRect")));//ת��Ϊ���ζ���
	//	mManager->setHitPoint(mManager->getHitRect().origin);
	//	mManager->setGetHitRect(RectFromString(e->Attribute("GetHitRect")));
	//	mManager->setGetHitPoint(mManager->getGetHitRect().origin);

	//	/*log("==type===%d",mManager->getType());

	//	int a=std::atoi(e->Attribute("ID"));
	//	log("%d",a);
	//	log("%s",str.c_str());*/
	//}

	//mManager->retain();//��ֹ���ͷţ��о����ü���

	////��ʾ����
	//auto monster=BaseRole::createWithProperty(mManager);
	//monster->setPosition(Vec2(800,200));
	//this->addChild(monster,2,1);

	//RoleCardController::getInstance()->monsterVec.push_back(monster);

	////���״̬��
	//BaseFSM * baseFSM=BaseFSM::createFSM(hero);
	//baseFSM->retain();
	//hero->setBaseFSM(baseFSM);

	//BaseFSM * baseFSM2=BaseFSM::createFSM(monster);
	//baseFSM2->retain();
	//monster->setBaseFSM(baseFSM2);


	////���ai
	//BaseAI * ai=BaseAI::createAI(hero);
	//ai->retain();
	//ai->startRoleAI();
	//hero->setBaseAI(ai);

	//BaseAI * ai2=BaseAI::createAI(monster);
	//ai2->retain();
	//ai2->startRoleAI();
	//monster->setBaseAI(ai2);

	////����Ӣ��id
	RoleCardController::getInstance()->setHeroID(1);

	//��ӱ���
	MapLayer * mapLayer=MapLayer::create();
	mapLayer->setBackGround("battleBg.jpg");
	this->addChild(mapLayer);

	//���ܰ�ť
	OperateLayer * operateLayer=OperateLayer::create();
	this->addChild(operateLayer);

	//���ҡ��
	rocker=HRocker::createHRocker("Direction_bt.png","Direction_bc.png",Vec2(200,200));
	rocker->startRocker(true);
	this->addChild(rocker);


	//�Ի���
	DialogLayer * dialog=DialogLayer::createWithJsonFile("1.json");
	this->addChild(dialog,10);

	this->scheduleUpdate();

	return true;

}

void ControlLayer::update( float dt )
{
	//��ҡ�˵ķ��򴫽���
	//hero->getBaseFSM()->switchMoveState(rocker->rockerDirection);
	if (RoleCardController::getInstance()->getHero()!=nullptr)
	{
		RoleCardController::getInstance()->getHero()->getBaseFSM()->switchMoveState(rocker->rockerDirection);
	}

	//�����
	std::vector<BaseRole *>::iterator itr=RoleCardController::getInstance()->monsterVec.begin();

	while (itr!=RoleCardController::getInstance()->monsterVec.end())
	{
		if ((*itr)->state==ROLE_FREE)
		{
			(* itr)->purge();
			RoleCardController::getInstance()->monsterVec.erase(itr);
			break;
		}

		++itr;

	}


	if (RoleCardController::getInstance()->monsterVec.size()==0)
	{
		log("win");


		if (DataManager::getInstance()->getLevelIndex()==2)
		{
			//���һ��
			return;
		}

		//
		this->purge();

		//��ȡ��һ������
		DataManager::getInstance()->setLevelIndex(DataManager::getInstance()->getLevelIndex()+1);
		tsm->toGameScene();
		//return;

	}

	//Ӣ�۵�
	itr=RoleCardController::getInstance()->heroVec.begin();

	while (itr!=RoleCardController::getInstance()->heroVec.end())
	{
		if ((*itr)->state==ROLE_FREE)
		{
			(* itr)->purge();
			RoleCardController::getInstance()->heroVec.erase(itr);
			break;
		}

		++itr;

	}


	if (RoleCardController::getInstance()->heroVec.size()==0)
	{
		log("fail");
	}



	
}

void ControlLayer::purge()
{
	Director::getInstance()->getScheduler()->unschedule(schedule_selector(ControlLayer::update),this);

	RoleCardController::getInstance()->purge();

	//this->removeFromParent();


}

