#include "raylib.h"

class UIElement;
class UIButton;
class UISlider;

class Module;

class PauseMenu
{
private:
	UIButton* pause = nullptr;
	UIButton* resume = nullptr;
	UIButton* settings = nullptr;
	UIButton* mainMenu = nullptr;
	Module* moduleAt = nullptr;

	Texture2D* bg_texture = nullptr;
	Texture2D* btn_texture = nullptr;
	Rectangle btn_rect = { 0,0,304,71};
	Rectangle btn_rect_hover = { 305,0,305,71};
	Rectangle btn_rect_pressed = { 305*2,0,305,71};
	bool paused=false;
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