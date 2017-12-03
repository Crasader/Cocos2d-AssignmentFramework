#ifndef __Scene2_H__
#define __Scene2_H__

#include "Player.h"

using namespace cocos2d;

class Scene2 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

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

	void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(Scene2);
private:
	GLProgram* proPostProcess;
	RenderTexture* rendtex;
	Sprite* rendtexSprite;

	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> Key_map;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	Player* player1;

	Node* bgNode;
	float bgX, bgY, bg2X, bg2Y;

	Vec2 bgSize;
};

#endif // __Scene2_SCENE_H__
