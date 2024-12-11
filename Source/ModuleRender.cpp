#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include <math.h>

ModuleRender::ModuleRender(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    background = BLACK;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRender::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
    ClearBackground(background);

    // NOTE: This function setups render batching system for
    // maximum performance, all consecutive Draw() calls are
    // not processed until EndDrawing() is called
    BeginDrawing();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
    // Draw everything in our batch!
    DrawFPS(10, 10);

    EndDrawing();

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	return true;
}

void ModuleRender::SetBackgroundColor(Color color)
{
	background = color;
}

// Draw to screen
<<<<<<< Updated upstream
bool ModuleRender::Draw(Texture2D texture, int x, int y, const Rectangle* section, double angle, int pivot_x, int pivot_y, Color tint ) const
=======
bool ModuleRender::Draw(Texture2D texture, int x, int y, const Rectangle* section, double angle, float scale, int pivot_x, int pivot_y, Color tint )
>>>>>>> Stashed changes
{
    bool ret = true;

    Rectangle rect = { 0.f, 0.f, (float)texture.width, (float)texture.height };

    if (section != NULL) rect = *section;

    // Create a destination rectangle based on the provided position and scale
    Rectangle destRect = { (float)(x - pivot_x) + camera.x,
                           (float)(y - pivot_y) + camera.y,
                           rect.width * scale, rect.height * scale };

    // Set the pivot point around which the texture will rotate (the center of rotation)
    Vector2 pivot = { (float)pivot_x, (float)pivot_y };

    // Rotate the texture using DrawTexturePro with the correct parameters
    DrawTexturePro(texture, rect, destRect, pivot, (float)angle, tint);

	return ret;
}

bool ModuleRender::DrawText(const char * text, int x, int y, Font font, int spacing, Color tint) const
{
    bool ret = true;

    Vector2 position = { (float)x, (float)y };

    DrawTextEx(font, text, position, (float)font.baseSize, (float)spacing, tint);

    return ret;
}
