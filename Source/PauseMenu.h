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

	Texture2D* bg_texture;
	Texture2D* btn_texture;
	Texture2D* btn_texture_hover;
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