#include "SceneManager.h"
#include "HelloWorldScene.h"
#include "Scene2.h"
#include "MenuScene.h"
#include "MasterManager.h"
#include "CreditScene.h"
#include "InstructionScene.h"
using namespace cocos2d;

#define ADDSCENE(SCENECLASS,SCENENAME)\
Add_Scene(SCENENAME, []()-> GenericScene* {\
return (GenericScene*)SCENECLASS::_createScene_withSceneNode();\
});

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
	//Add_Scene((GenericScene*)temp, "HelloWorld");


	/*Add_Scene("HelloWorld", []()-> GenericScene* {
		return (GenericScene*)HelloWorld::_createScene_withSceneNode();
	});*/

	//ADDSCENE(HelloWorld, "HelloWorld");
	//ADDSCENE(Scene2, "Scene2");
	//ADDSCENE(MenuScene, "MenuScene");

	Add_Scene("HelloWorld", []() {
		return HelloWorld::_createScene_withSceneNode();
	});
	Add_Scene("Scene2", []() {
		return Scene2::_createScene_withSceneNode();
	});
	Add_Scene("MenuScene", []() {
		return MenuScene::_createScene_withSceneNode();
	});

	Add_Scene("CreditScene", []() {
		return CreditScene::_createScene_withSceneNode();
	});

	Add_Scene("InstructionScene", []() {
		return InstructionScene::_createScene_withSceneNode();
	});

	currSceneName = "";

	currScene_playingSize = Director::getInstance()->getVisibleSize();
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

void SceneManager::Add_Scene(string scene_name, Scene* (*fp)())
{
	//m_Scene_Map_Create.insert(pair<string, GenericScene* (*)()>(scene_name, fp));
	SceneInfo temp;
	temp.createfunc = fp;
	temp.name = scene_name;
	m_SceneInfoList.push_back(temp);
}

void SceneManager::Change_Scene(string scene_name)
{

	m_curr_scene->On_Change_Scene(true);
	for (int i = 0; i < m_SceneInfoList.size(); ++i)
	{
		if (m_SceneInfoList[i].name == scene_name)
		{
			m_curr_scene = dynamic_cast<GenericScene*>(m_SceneInfoList[i].createfunc());
			currSceneName = m_SceneInfoList[i].name;
			CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5f, m_curr_scene->get_SceneNode()));
			MasterManager::getInstance().Init();
			CCLOG("ChangeScene SUCCESS");
			return;
		}
	}
	CCLOG("ChangeScene FAILED");
}

void SceneManager::Run_Scene(string scene_name)
{
	//GenericScene* scene = m_Scene_Map_Create.find(scene_name)->second();
	////m_curr_scene = dynamic_cast<GenericScene*>(scene->_createScene());//dynamic_cast<GenericScene*>(scene->createScene());
	//CCDirector::getInstance()->runWithScene(scene->get_SceneNode());
	//m_curr_scene = scene;
	//currScene_playingSize = Director::getInstance()->getVisibleSize();//m_curr_scene->get_playingSize();

	for (int i = 0; i < m_SceneInfoList.size(); ++i)
	{
		if (m_SceneInfoList[i].name == scene_name)
		{
			m_curr_scene = dynamic_cast<GenericScene*>(m_SceneInfoList[i].createfunc());
			currSceneName = m_SceneInfoList[i].name;
			CCDirector::getInstance()->runWithScene(m_curr_scene->get_SceneNode());
			widthHeight_ratio = CCDirector::getInstance()->getVisibleSize().width / CCDirector::getInstance()->getVisibleSize().height;
			MasterManager::getInstance().Init();
			CCLOG("RunScene SUCCESS");
			return;
		}
	}
	CCLOG("RunScene FAILED");
	
}


Size SceneManager::AdjustContentSize(Size originalcontentsize, float ratioToScreenHeight)
{
	Size adjusted;
	float originalratio = originalcontentsize.width / originalcontentsize.height;
	adjusted.height = SceneManager::getInstance().currScene_playingSize.height * ratioToScreenHeight;
	adjusted.width = originalratio * adjusted.height;
	return adjusted;
}

void SceneManager::AdjustContentSize(Sprite* sprite, float ratioToScreenHeight)
{
	Size adjusted;
	float originalratio = sprite->getContentSize().width / sprite->getContentSize().height;
	adjusted.height = SceneManager::getInstance().currScene_playingSize.height * ratioToScreenHeight;
	adjusted.width = originalratio * adjusted.height;
	sprite->setContentSize(adjusted);
}