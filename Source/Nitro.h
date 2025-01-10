class Timer;
class Module;
class Vehicle;
class Nitro
{
private:
	float speedMultiplier = 2.5f;
	float maxSecondsEnabled = 7;
	float minSecondsToEnabled = 1.5f;
	float currentSecondsEnabled = 7;
	bool isEnabled = false;
	Timer* enabledTimer = nullptr;
	Module* moduleAt;
	Vehicle* vehicle;
public:
	Nitro(Module* ModuleAtAt, Vehicle* v);
	~Nitro();
	void Enable();
	void Disable();
	float GetNitroMultiplier();
	bool IsEnabled();
	void Update();
	void Render();
	void CleanUp();
};