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
		GenericManager(*it)();
	}
}

void MasterManager::Update(float dt)
{
	vector<updatefunctionpointer>::iterator it = Update_list.begin();
	for (; it != Update_list.end(); ++it)
	{
		(*it)(dt);
	}
}

void MasterManager::Add_Init_Function(Initfunctionpointer fp)
{
	Init_list.push_back(fp);
	CCLOG("Init function added");
}

void MasterManager::Add_Update_Function(updatefunctionpointer fp)
{
	Update_list.push_back(fp);
}