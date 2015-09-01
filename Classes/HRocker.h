#ifndef __HROCKER_H__
#define __HROCKER_H__

#include "cocos2d.h"

USING_NS_CC;

//用于标识摇杆还有摇杆的背景
typedef enum
{
	tag_rocker,
	tag_rockerBG
}tagForHRocker;

//摇杆的方向
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
 * 摇杆
 * 
*/	
class HRocker:public Layer
{
public:
	static HRocker * createHRocker(const char * rockerImgName,
		const char * rockerBGImageName,Vec2 position);

	void startRocker(bool _isStopOther);
	void stopRocker();

	int rockerDirection;//方向
	bool rockerRun;//当前人物的行走方向，用来判断人物的行走方向

	CREATE_FUNC(HRocker);

private:
	//初始化
	void rockerInit(const char * rockerImgName,
		const char * rockerBGImageName,Vec2 position);
	//标志摇杆是否可以操作
	bool isCanMove;

	//获取当前摇杆与用户触摸点的角度
	float getRad(Vec2 pos1,Vec2 pos2);

	//保存摇杆的背景坐标与半径
	Vec2 rockerBGPosition;
	float rockerBGR;

	//触摸事件的回调方法
	bool onTouchBegin(Touch * touch ,Event * unused_event);
	void onTouchMoved(Touch * touch ,Event * unused_event);
	void onTouchEnded(Touch * touch ,Event * unused_event);

	//根据半径和角度求得最终位置
	Vec2 getAnglePosition(float r,float angle);


};

#endif // __HELLOWORLD_SCENE_H__