#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

class InputManager
{
public:
	static InputManager& getInstance()
	{
		static InputManager Instance;
		return Instance;
	}
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	void Init();
	void Update(float dt);


private:
	InputManager();
	~InputManager();
};



#endif