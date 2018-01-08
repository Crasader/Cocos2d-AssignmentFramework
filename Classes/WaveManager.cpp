#include "WaveManager.h"

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

}

void WaveManager::Run_next_wave()
{
	Wave* temp = Wave_List.front();
	temp->Run();
	Wave_List.pop_front();
	delete temp;
}