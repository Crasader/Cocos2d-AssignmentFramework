#ifndef MANAGER_MACRO_H_
#define MANAGER_MACRO_H_
//
//#define MASTERMANAGER_CALLBACK_INIT_ (__CLASS,FUNCTION)			\
//{																			\
//	__CLASS* instance = this;											\
//	MasterManager::getInstance().Add_Init_Function([&instance]() {			\
//		instance->FUNCTION();												\
//	});																		\
//}

#define MASTERMANAGER_CALLBACK_UPDATE_FUNC(CLASS,FUNC)\
{\
	CLASS* instance = this;\
	MasterManager::getInstance().Add_Update_Function([&instance](float dt) {\
		instance->FUNC(dt);\
	});\
	CCLOG("Update function added");\
}

#define MASTERMANAGER_CALLBACK_INIT_FUNC(CLASS,FUNC)\
{\
	CLASS* instance = this;\
	MasterManager::getInstance().Add_Init_Function([&instance]() {\
		instance->FUNC();\
	});\
	CCLOG("Init function added");\
}

#endif