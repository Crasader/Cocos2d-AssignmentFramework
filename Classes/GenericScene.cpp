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
}

