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
	//�ؿ���Ϣ���ַ��������ڴ��ݽ�������json����Ҫת��Ϊ�ַ����Ա����
	std::string tollgateData;

	std::vector<std::string> _levelDataArray;
	CC_SYNTHESIZE(int,levelIndex,LevelIndex);


};

#endif // __HELLOWORLD_SCENE_H__