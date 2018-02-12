#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::Init()
{
	if (!particleEmitter)
		particleEmitter = ParticleExplosion::create();
}

void ParticleManager::Update(float dt)
{

}