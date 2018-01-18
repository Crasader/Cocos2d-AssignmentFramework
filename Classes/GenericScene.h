#ifndef GENERIC_SCENE_H_
#define GENERIC_SCENE_H_
#include "Player.h"
#include "EnemyManager.h"
#include "PowerUp.h"
using namespace cocos2d;
class GenericScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	// implement the "static create()" method manually
	CREATE_FUNC(GenericScene);
	virtual bool init();


private:

};


#endif