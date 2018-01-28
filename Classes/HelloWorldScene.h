#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

//#include "Player.h"
//#include "EnemyManager.h"
//#include "PowerUp.h"
#include "GenericScene.h"
using namespace cocos2d;

class HelloWorld : GenericScene
{
public:
    static cocos2d::Scene* createScene();
	virtual cocos2d::Scene* _createScene();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode, bool seconds);
	bool checkBoxCollision(Sprite* box1, Sprite* box2);

	virtual void onMouseMove(Event*);
	virtual void onMouseUp(Event*);
	virtual void onMouseDown(Event*);
	virtual void onMouseScroll(Event*);
    
	virtual void update(float delta);
	virtual Scene* get_SceneNode();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	//GLProgram* proPostProcess;
	//RenderTexture* rendtex;
	//Sprite* rendtexSprite;
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> Key_map;

	

	Player* player1;
	PowerUp* powerUp;

	Enemy* enemyInstance;


	Node* bgNode;
	float bgX, bgY, bg2X, bg2Y;

	Vec2 bgSize;
};

#endif // __HELLOWORLD_SCENE_H__
