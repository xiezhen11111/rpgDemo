#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class DataManager:public Layer
{
public:
	static DataManager * getInstance();

	void initWithJsonFile(const char * fileName);

	std::vector<std::string> getLevelDataArrayByIndex(int index);

public:
	//关卡信息的字符串，由于传递进来的是json，需要转换为字符串以便解析
	std::string tollgateData;

	std::vector<std::string> _levelDataArray;
	CC_SYNTHESIZE(int,levelIndex,LevelIndex);


};

#endif // __HELLOWORLD_SCENE_H__