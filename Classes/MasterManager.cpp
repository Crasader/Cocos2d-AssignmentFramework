#include "MasterManager.h"
//vector<updatefunctionpointer> MasterManager::Update_list;
//vector<Initfunctionpointer> MasterManager::Init_list;


MasterManager::MasterManager()
{
}

MasterManager::~MasterManager()
{
}

void MasterManager::Init()
{
	vector<Initfunctionpointer>::iterator it = Init_list.begin();
	for (; it != Init_list.end();++it)
	{
		//GenericManager(*it)();
	}
}

void MasterManager::Update(float dt)
{
	vector<updatefunctionpointer>::iterator it = Update_list.begin();
	for (; it != Update_list.end(); ++it)
	{
		//GenericManager(*it)(dt);
	}
}
//template <class T>
void MasterManager::Add_Init_Function(Initfunctionpointer t)
{
	/*Init_list.push_back([target]()
	{
		target::Init();
	});*/

	Init_list.push_back(t);
	CCLOG("Init function added");
}
//template <class T>
void MasterManager::Add_Update_Function(updatefunctionpointer t)
{
	//updatefunctionpointer temp = fp;
	/*Update_list.push_back([target](float dt) 
	{
		target::Update(dt);
	});*/
	Update_list.push_back(t);
	CCLOG("Update function added");
}