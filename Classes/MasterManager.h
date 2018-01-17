#ifndef MASTER_MANAGER_H
#define MASTER_MANAGER_H

#include "cocos2d.h"
#include "GenericManager.h"
using namespace std;
using namespace cocos2d;

typedef std::function<void(float)> updatefunctionpointer;//void (GenericManager::* updatefunctionpointer)(float);
typedef std::function<void()> Initfunctionpointer;//void (GenericManager::* Initfunctionpointer)();


class MasterManager
{
public:
	static MasterManager& getInstance()
	{
		static MasterManager Instance;
		return Instance;
	}
	MasterManager(const MasterManager&) = delete;
	MasterManager& operator=(const MasterManager&) = delete;
	void Init();
	void Update(float dt);
	//template <class T>
	void Add_Init_Function(Initfunctionpointer t);//T *target, string classname);
	//template <class T>
	void Add_Update_Function(updatefunctionpointer t);//T *target, string classname);


	
public:
	vector<updatefunctionpointer> Update_list;
	vector<Initfunctionpointer> Init_list;
private:
	MasterManager();
	~MasterManager();
	
};



#endif