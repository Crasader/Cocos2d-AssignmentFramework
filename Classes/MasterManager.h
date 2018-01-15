#ifndef MASTER_MANAGER_H
#define MASTER_MANAGER_H

#include "cocos2d.h"
#include "GenericManager.h"
using namespace std;
using namespace cocos2d;

typedef void (GenericManager::*updatefunctionpointer)(float);
typedef void (GenericManager::*Initfunctionpointer)();
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
	void Add_Init_Function(Initfunctionpointer i_fp);
	void Add_Update_Function(updatefunctionpointer u_fp);


	
public:
	vector<updatefunctionpointer> Update_list;
	vector<Initfunctionpointer> Init_list;
private:
	MasterManager();
	~MasterManager();
	
};



#endif