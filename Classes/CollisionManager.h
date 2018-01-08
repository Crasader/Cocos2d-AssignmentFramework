#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

class CollisionManager
{
public:
	static CollisionManager& getInstance()
	{
		static CollisionManager Instance;
		return Instance;
	}
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	void Init();
	void Update(float dt);


private:
	CollisionManager();
	~CollisionManager();
};



#endif