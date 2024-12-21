#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include <math.h>

ModuleRender::ModuleRender(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    background = GRAY;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;

    for (size_t i = 0; i < DEBUG_LAYER_DO_NOT_USE; i++)
    {
        CreateLayer((RenderLayer)i);
    }

    cursor.SetCursor("Assets/Textures/Cursor.png");

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRender::PreUpdate()
{
    ClearBackground(background);
    for (size_t i = 0; i < layers.size(); i++)
    {
        CleanRenderLayer(layers[i]);
    }
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
   

    // NOTE: This function setups render batching system for
    // maximum performance, all consecutive Draw() calls are
    // not processed until EndDrawing() is called
    BeginDrawing();
    for (size_t i = 0; i < layers.size(); i++)
    {
        RenderLayerToScreen(layers[i]);
    }

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{

    // Draw everything in our batch!
    
    cursor.RenderCursor();
    DrawFPS(10, 10);

    EndDrawing();

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
    for (size_t i = 0; i < layers.size(); i++)
    {
        UnloadRenderTexture(layers[i].data);
    }
    layers.clear();
	return true;
}

void ModuleRender::SetBackgroundColor(Color color)
{
	background = color;
}

// Draw to screen
bool ModuleRender::Draw(Texture2D texture, Vector2 position, Vector2 offset, const Rectangle* section, double angle, float scale, int pivot_x, int pivot_y, Color tint )
{
    BeginTextureMode(layers.at(currentRenderLayer).data);
    bool ret = true;

    double radians = DEG2RAD * (angle);
    offset = {
       (float)(cos(radians) * offset.x - sin(radians) * offset.y) ,
        (float)(sin(radians) * offset.x + cos(radians) * offset.y)
    };

    offset = { offset.x * scale, offset.y * scale };

    Rectangle rect = { 0.f, 0.f, (float)texture.width, (float)texture.height };

    if (section != NULL) rect = *section;

    // Create a destination rectangle based on the provided position and scale
    Rectangle destRect = { (float)(position.x + offset.x - pivot_x ),
                           (float)(position.y + offset.y - pivot_y),
                           rect.width * scale, rect.height * scale };

    // Set the pivot point around which the texture will rotate (the center of rotation)
    Vector2 pivot = { (float)pivot_x, (float)pivot_y };

    // Rotate the texture using DrawTexturePro with the correct parameters
    DrawTexturePro(texture, rect, destRect, pivot, (float)angle, tint);
    EndTextureMode();
    if (!IsRenderLayerBlocked())
        ResetRenderLayer();
	return ret;
}

bool ModuleRender::DrawText(const char * text, Vector2 position, Vector2 offset, Font font, int spacing, Color tint)
{
    BeginTextureMode(layers.at(currentRenderLayer).data);
    bool ret = true;
    position = { (float)position.x + offset.x, (float)position.y + offset.y };

    DrawTextEx(font, text, position, (float)font.baseSize, (float)spacing, tint);
    EndTextureMode();
    if (!IsRenderLayerBlocked())
        ResetRenderLayer();
    return ret;
}

void ModuleRender::SelectRenderLayer(RenderLayer layer)
{
    currentRenderLayer = layer;
}

ModuleRender::RenderLayer ModuleRender::GetCurrentRenderLayer()
{
    return currentRenderLayer;
}

void ModuleRender::BlockRenderLayer(RenderLayer layer)
{
    BlockRenderLayer();
    SelectRenderLayer(layer);
}

void ModuleRender::BlockRenderLayer()
{
    blockRenderLayer = true;
}

void ModuleRender::UnlockRenderLayer()
{
    blockRenderLayer = false;
    ResetRenderLayer();
}

bool ModuleRender::IsRenderLayerBlocked()
{
    return blockRenderLayer;
}

void ModuleRender::ResetRenderLayer()
{
    currentRenderLayer = DEFAULT;
}

void ModuleRender::RenderLayerToScreen(Layer layer)
{
    Rectangle sourceRect = { 0, 0, (float)layer.data.texture.width, (float)-layer.data.texture.height };
    Rectangle destRect = { 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };

    // Draw the layer's texture to the screen, flipping vertically
    DrawTexturePro(layer.data.texture, sourceRect, destRect, { 0, 0 }, 0, WHITE);
}

void ModuleRender::CreateLayer(RenderLayer layer)
{
    RenderTexture2D texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    layers.push_back({layer, texture});
}

void ModuleRender::CleanRenderLayer(Layer layer)
{
    BeginTextureMode(layer.data);
    ClearBackground(BLANK);
    EndTextureMode();
}
