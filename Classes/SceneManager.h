#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "cocos2d.h"

using namespace cocos2d;

enum class SceneType
{
	NONE,
	SCENE1,
	SCENE2
};


class SceneManager
{
public:
	static SceneManager& getInstance();
	~SceneManager();
	void runSceneWithType(const SceneType sceneType);
	void returnToPrevScene();

	Size currScene_playingSize;
private:
	SceneType _prevSceneType;
	SceneType _currSceneType;
	SceneManager();

};

#endif // SCENEMANAGER_H