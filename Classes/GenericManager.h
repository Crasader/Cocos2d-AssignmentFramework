#ifndef GENERIC_MANAGER_H_
#define GENERIC_MANAGER_H_
#include "ManagerMacro.h"
#include "GlobalDeclarations.h"
class GenericManager
{
public:
	static GenericManager& getInstance()
	{
		static GenericManager Instance;
		return Instance;
	}
	virtual void Init();
	virtual void Update(float dt);

protected:
	GenericManager();
	~GenericManager();
};


#endif