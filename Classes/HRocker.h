#ifndef __HROCKER_H__
#define __HROCKER_H__

#include "cocos2d.h"

USING_NS_CC;

//���ڱ�ʶҡ�˻���ҡ�˵ı���
typedef enum
{
	tag_rocker,
	tag_rockerBG
}tagForHRocker;

//ҡ�˵ķ���
typedef enum
{
	rocker_stay=0,
	rocker_right,
	rocker_up,
	rocker_left,
	rocker_down,

}tagDirection;


/**
 * 
 * ҡ��
 * 
*/	
class HRocker:public Layer
{
public:
	static HRocker * createHRocker(const char * rockerImgName,
		const char * rockerBGImageName,Vec2 position);

	void startRocker(bool _isStopOther);
	void stopRocker();

	int rockerDirection;//����
	bool rockerRun;//��ǰ��������߷��������ж���������߷���

	CREATE_FUNC(HRocker);

private:
	//��ʼ��
	void rockerInit(const char * rockerImgName,
		const char * rockerBGImageName,Vec2 position);
	//��־ҡ���Ƿ���Բ���
	bool isCanMove;

	//��ȡ��ǰҡ�����û�������ĽǶ�
	float getRad(Vec2 pos1,Vec2 pos2);

	//����ҡ�˵ı���������뾶
	Vec2 rockerBGPosition;
	float rockerBGR;

	//�����¼��Ļص�����
	bool onTouchBegin(Touch * touch ,Event * unused_event);
	void onTouchMoved(Touch * touch ,Event * unused_event);
	void onTouchEnded(Touch * touch ,Event * unused_event);

	//���ݰ뾶�ͽǶ��������λ��
	Vec2 getAnglePosition(float r,float angle);


};

#endif // __HELLOWORLD_SCENE_H__