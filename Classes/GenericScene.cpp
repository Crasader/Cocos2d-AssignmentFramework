#include "GenericScene.h"

GenericScene::GenericScene()
{
}

GenericScene::~GenericScene()
{
}

Scene* GenericScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GenericScene::create();
	scene->addChild(layer);
	return scene;
}

bool GenericScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	init_Generic_only();	
}

bool GenericScene::init_Generic_only()
{
	for each (void(*fp) () in List_of_Init_func)
	{
		fp();
	}

	m_initialzed = true;
}

void GenericScene::Add_Init_Function(void(*fp) ())
{
	List_of_Init_func.push_back(fp);
}

void GenericScene::update(float delta)
{

}

void GenericScene::On_Change_Scene(bool away)
{

}

void GenericScene::Exit()
{

}