#include "SceneManager.h"
#include "HelloWorldScene.h"
#include "Scene2.h"
#include "MasterManager.h"
using namespace cocos2d;

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

SceneManager::SceneManager() :
	_prevSceneType(SceneType::SCENE1),
	_currSceneType(SceneType::SCENE1)
{
	//MASTERMANAGER_CALLBACK_INIT_FUNC(SceneManager, Init)
	//MASTERMANAGER_CALLBACK_UPDATE_FUNC(SceneManager, Update)
}

SceneManager::~SceneManager()
{

}

void SceneManager::runSceneWithType(const SceneType sceneType)
{
	Scene* sceneToRun = nullptr;

	switch (sceneType)
	{
	case SceneType::SCENE1:
		sceneToRun = HelloWorld::createScene();
		break;
	case SceneType::SCENE2:
		sceneToRun = Scene2::createScene();
		break;
	default:
		sceneToRun = HelloWorld::createScene();
		break;
	}

	SceneType oldSceneType = _currSceneType;
	_currSceneType = sceneType;
	sceneToRun->setTag(static_cast<int>(sceneType));

	if (sceneToRun == nullptr)
	{
		_currSceneType = oldSceneType;
		return;
	}

	_prevSceneType = oldSceneType;
	if (CCDirector::getInstance()->getRunningScene() == nullptr)
	{
		CCDirector::getInstance()->runWithScene(sceneToRun);
	}
	else
	{
		CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5f, sceneToRun));
	}
}

void SceneManager::returnToPrevScene()
{
	this->runSceneWithType(_prevSceneType);
}