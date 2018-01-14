#include "WaveManager.h"

using namespace cocos2d;

WaveManager::WaveManager()
{
}

WaveManager::~WaveManager()
{
}

void WaveManager::Init()
{
	Wave* temp = Wave::Create(5);
	Wave_List.push_back(temp);

	
}

void WaveManager::Update(float dt)
{
	if (Wave_List.size() != 0)
	{
		Wave_List.front()->Update(dt);
		if (Wave_List.front()->finished)
		{
			Wave* temp = Wave_List.front();
			Wave_List.pop_front();
			delete temp;
		}			
	}
}

void WaveManager::Run_next_wave()
{
	if (Wave_List.size() == 0)
		return;
	Wave* temp = Wave_List.front();
	temp->Run();
}

void WaveManager::Add_wave(Wave* wave)
{
	Wave_List.push_back(wave);
}

