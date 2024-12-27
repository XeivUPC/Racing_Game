#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include <raymath.h>

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init window");
	bool ret = true;

	unsigned int flags = 0;
	bool fullscreen = WIN_FULLSCREEN;
	bool borderless = WIN_BORDERLESS;
	bool resizable = WIN_RESIZABLE;
	bool vsync = VSYNC;

	game_width = SCREEN_WIDTH;
	game_height = SCREEN_HEIGHT;

	if (fullscreen == true) flags |= FLAG_FULLSCREEN_MODE;

	if (borderless == true) flags |= FLAG_WINDOW_UNDECORATED;

	if (resizable == true) flags |= FLAG_WINDOW_RESIZABLE;

    if (vsync == true) flags |= FLAG_VSYNC_HINT;

    LOG("Init raylib window");

    SetConfigFlags(flags);
	InitWindow(game_width, game_height, TITLE);
	SetWindowMinSize(MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT);
	SetTargetFPS(60);

	return ret;
}

// Called each loop iteration
update_status ModuleWindow::PreUpdate()
{
    if (WindowShouldClose()) windowEvents[WINDOW_EVENT_QUIT] = true;
    if (IsWindowMinimized()) windowEvents[WINDOW_EVENT_HIDE] = true;
    //if (IsWindowRestored()) windowEvents[WINDOW_EVENT_SHOW] = true;   // Not available
    if (IsWindowResized()) windowEvents[WINDOW_EVENT_RESIZE] = true;

    return UPDATE_CONTINUE;
}

update_status ModuleWindow::Update()
{

	scale = (float)MIN((float)GetScreenWidth() / (float)game_width, (float)GetScreenHeight() / (float)game_height);

	return UPDATE_CONTINUE;
}

update_status ModuleWindow::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Close window");

    CloseWindow();

	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SetWindowTitle(title);
}

uint ModuleWindow::GetLogicWidth() const
{
	return game_width;
}

uint ModuleWindow::GetLogicHeight() const
{
	return game_height;
}

float ModuleWindow::GetRealWidth() const
{
	return (float)game_width * scale;
}

float ModuleWindow::GetRealHeight() const
{
	return (float)game_height * scale;
}

float ModuleWindow::GetScale() const
{
	return scale;
}

Vector2 ModuleWindow::GetVirtualMousePos()
{
	Vector2 mouse = GetMousePosition();
	Vector2 virtualMouse = { 0 };
	virtualMouse.x = (mouse.x - (GetScreenWidth() - GetRealWidth()) * 0.5f) / scale;
	virtualMouse.y = (mouse.y - (GetScreenHeight() - GetRealHeight()) * 0.5f) / scale;
	virtualMouse = Vector2Clamp(virtualMouse, { 0, 0 }, { (float)game_width, (float)game_height });

	return virtualMouse;
}

bool ModuleWindow::GetWindowEvent(WindowEvent ev)
{
    return windowEvents[ev];
}