#include "DataManager.h"
#include "json/rapidjson.h"
#include "json/document.h"

using namespace rapidjson;

static DataManager * dataManager=nullptr;

DataManager * DataManager::getInstance()
{
	if (dataManager==nullptr)
	{
		dataManager=new DataManager();
	}


	return dataManager;

}

void DataManager::initWithJsonFile( const char * fileName )
{
	tollgateData=FileUtils::getInstance()->getStringFromFile(fileName);
	log("´òÓ¡jsonÊý¾Ý %s",tollgateData.c_str());


}

std::vector<std::string> DataManager::getLevelDataArrayByIndex( int index )
{
	Document doc;

	doc.Parse<kParseDefaultFlags>(tollgateData.c_str());
	_levelDataArray.clear();
	rapidjson::Value &array=doc["Tollgate"];


	if (array.IsArray())
	{
		int i=index;
		int j=0;
		for (j=0;j<array[i]["RoleData"].Size();j++)
		{
			rapidjson::Value & str=array[i]["RoleData"][j];
			log("test str is %s",str.GetString());
			_levelDataArray.push_back(str.GetString());
		}

	}


	return _levelDataArray;
}

