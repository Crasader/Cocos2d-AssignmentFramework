#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "cocos2d.h"
#include "GenericManager.h"
#include "GenericScene.h"
using namespace cocos2d;
//
//enum class SceneType
//{
//	NONE,
//	SCENE1,
//	SCENE2
//};


class SceneManager : GenericManager
{
public:
	SINGLETON_CLASS(SceneManager)
	virtual void Init();
	virtual void Update(float dt);
	GenericScene* get_current_scene();
	//bool set_current_scene(string scene_name);
	//void Add_Scene(GenericScene* scene, string scene_name);
	void Add_Scene(GenericScene* scene, string scene_name);
	void Change_Scene(string scene_name);
	void Run_Scene(string scene_name);
	Size currScene_playingSize;
private:
	~SceneManager();
	SceneManager();

	map<string,GenericScene*> m_Scene_Map;
	//map<string, GenericScene*> m_running_Scene_Map;
	vector<GenericScene*> Running_scene_list;
	GenericScene* m_curr_scene;
};

#endif // SCENEMANAGER_H