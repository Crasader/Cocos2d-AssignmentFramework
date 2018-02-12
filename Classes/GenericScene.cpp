#include "GenericScene.h"
#include "MasterManager.h"

Scene* GenericScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = create();
	scene->addChild(layer);
	return scene;
}

//cocos2d::Scene* GenericScene::_createScene()
//{
//	auto scene_Node = Scene::createWithPhysics();
//	auto layer = create();
//	layer->set_SceneNode(scene_Node);
//	scene_Node->addChild(layer);
//	return layer;
//}

bool GenericScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	return init_Generic_only();
}

bool GenericScene::init_Generic_only()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));


	m_MenuLayer = Menu::create();
	m_MenuLayer->setPosition(0.f, 0.f);
	this->addChild(m_MenuLayer,100);
	//MasterManager::getInstance().Init();

	/*for each (void(*fp) () in List_of_Init_func)
	{
		fp();
	}*/
	for (int i = 0; i < List_of_Init_func.size(); ++i)
	{
		List_of_Init_func[i]();
	}

	m_initialzed = true;

	return true;
}

void GenericScene::Add_Init_Function(void(*fp) ())
{
	List_of_Init_func.push_back(fp);
}

void GenericScene::Add_Update_Function(void(*fp) (float))
{
	List_of_Update_func.push_back(fp);
}

void GenericScene::update(float delta)
{
	/*for each (void(*fp) (float) in List_of_Update_func)
	{
		fp(delta);
	}*/
	for (int i = 0; i < List_of_Update_func.size(); ++i)
	{
		List_of_Update_func[i](delta);
	}
}

Size GenericScene::get_playingSize()
{
	return playingSize;
}

void GenericScene::On_Change_Scene(bool away)
{

}

void GenericScene::Exit()
{

}

Scene* GenericScene::get_SceneNode()
{
	return sceneNode;
}

void GenericScene::set_SceneNode(Scene* scenenode)
{
	sceneNode = scenenode;
}