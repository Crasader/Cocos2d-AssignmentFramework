#ifndef PARTICLE_MANAGER_H_
#define PARTICLE_MANAGER_H_
#include "cocos2d.h"
#include "GenericManager.h"
using namespace cocos2d;
using namespace std;

class ParticleManager
{
public:
	SINGLETON_CLASS(ParticleManager)
	void Init();
	void Update(float dt);


private:
	ParticleManager();
	~ParticleManager();

	ParticleExplosion* particleEmitter;
};



#endif