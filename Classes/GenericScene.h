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
	bool init_Generic_only();
	virtual void Add_Init_Function(void(*fp) ());
	virtual void update(float delta);
	virtual void On_Change_Scene(bool away);
	virtual void Exit();
protected:
	bool m_initialzed = false;
	vector<void(*) ()> List_of_Init_func;
	GLProgram* proPostProcess;
	RenderTexture* rendtex;
	Sprite* rendtexSprite;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
};


#endif