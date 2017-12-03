#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

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

private:
	SceneType _prevSceneType;
	SceneType _currSceneType;
	SceneManager();

};

#endif // SCENEMANAGER_H