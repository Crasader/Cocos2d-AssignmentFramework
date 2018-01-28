#include "SceneManager.h"
#include "HelloWorldScene.h"
#include "Scene2.h"
#include "MasterManager.h"
using namespace cocos2d;/*

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}*/

SceneManager::SceneManager() /*:
	_prevSceneType(SceneType::SCENE1),
	_currSceneType(SceneType::SCENE1)*/
{
	//MASTERMANAGER_CALLBACK_INIT_FUNC(SceneManager, Init)
	//MASTERMANAGER_CALLBACK_UPDATE_FUNC(SceneManager, Update)
}

SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	HelloWorld* temp = (HelloWorld*)HelloWorld::_createScene_withSceneNode();
	Add_Scene((GenericScene*)temp, "HelloWorld");
}

void SceneManager::Update(float dt)
{

}

GenericScene* SceneManager::get_current_scene()
{
	return m_curr_scene;
}

//bool SceneManager::set_current_scene(string scene_name)
//{
//	m_curr_scene = m_Scene_Map.find(scene_name)->second;
//	if (m_curr_scene)
//		return true;
//	return false;	
//}

//void SceneManager::Add_Scene(GenericScene* scene, string scene_name)
//{
//	m_Scene_Map.insert(pair<string, GenericScene*>(scene_name, scene));
//}

void SceneManager::Add_Scene(GenericScene* scene, string scene_name)
{
	m_Scene_Map.insert(pair<string, GenericScene*>(scene_name, scene));
}

void SceneManager::Change_Scene(string scene_name)
{
	//delete scene stuff here if needed
	m_curr_scene->On_Change_Scene(true);
	GenericScene* scene = m_Scene_Map.find(scene_name)->second;
	m_curr_scene = dynamic_cast<GenericScene*>(scene->_createScene());
	//scene stuff here
	CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5f, dynamic_cast<Scene*>(m_curr_scene)));
}

void SceneManager::Run_Scene(string scene_name)
{
	GenericScene* scene = m_Scene_Map.find(scene_name)->second;
	//m_curr_scene = dynamic_cast<GenericScene*>(scene->_createScene());//dynamic_cast<GenericScene*>(scene->createScene());
	CCDirector::getInstance()->runWithScene(scene->get_SceneNode());
	m_curr_scene = scene;
}

//void SceneManager::runSceneWithType(const SceneType sceneType)
//{
//	Scene* sceneToRun = nullptr;
//
//	switch (sceneType)
//	{
//	case SceneType::SCENE1:
//		sceneToRun = HelloWorld::createScene();
//		break;
//	case SceneType::SCENE2:
//		sceneToRun = Scene2::createScene();
//		break;
//	default:
//		sceneToRun = HelloWorld::createScene();
//		break;
//	}
//
//	SceneType oldSceneType = _currSceneType;
//	_currSceneType = sceneType;
//	sceneToRun->setTag(static_cast<int>(sceneType));
//
//	if (sceneToRun == nullptr)
//	{
//		_currSceneType = oldSceneType;
//		return;
//	}
//
//	_prevSceneType = oldSceneType;
//	if (CCDirector::getInstance()->getRunningScene() == nullptr)
//	{
//		CCDirector::getInstance()->runWithScene(sceneToRun);
//	}
//	else
//	{
//		CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5f, sceneToRun));
//	}
//}
//
//void SceneManager::returnToPrevScene()
//{
//	this->runSceneWithType(_prevSceneType);
//}
