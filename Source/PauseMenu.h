#include "raylib.h"

class UIElement;
class UIButton;
class UISlider;

class Module;

class PauseMenu
{
private:
	UIButton* pause;
	UIButton* resume;
	UIButton* settings;
	UIButton* mainMenu;
	Module* moduleAt;
	Texture2D* texture;
	Rectangle rect;
	bool paused;
public:
	PauseMenu(Module* moduleat);
	~PauseMenu();
	bool Start();
	bool Update();
	bool Render();
	bool CleanUp();
	bool IsPaused();
	void Pause();
	void Resume();
	void Settings();
	void MainMenu();
};