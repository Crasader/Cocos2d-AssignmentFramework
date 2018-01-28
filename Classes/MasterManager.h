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
	SINGLETON_CLASS(MasterManager)
	void Init();
	void update(float dt);
	//template <class T>
	void Add_Init_Function(Initfunctionpointer t);
	/*template <class T>
	void Add_Init_Function(T* instance);*/
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