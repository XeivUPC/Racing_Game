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

    for (size_t i = 0; i < DEBUG_LAYER_DO_NOT_USE; i++)
    {
        CreateLayer((RenderLayer)i);
    }

    cursor.SetCursor("Assets/Textures/Cursor.png");

    camera = { 0 };
    camera.target = { 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

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
    
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
   
    // Draw everything in our batch!
    
    for (size_t i = 0; i < layers.size(); i++)
    {
        RenderLayerToScreen(layers[i]);
    }
    
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
    if (IsCameraMode())
        BeginMode2D(camera);
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
                           abs(rect.width) * scale, abs(rect.height) * scale };

    // Set the pivot point around which the texture will rotate (the center of rotation)
    Vector2 pivot = { (float)pivot_x, (float)pivot_y };

    // Rotate the texture using DrawTexturePro with the correct parameters
    DrawTexturePro(texture, rect, destRect, pivot, (float)angle, tint);
    if (IsCameraMode())
        EndMode2D();
    EndTextureMode();
    if (!IsRenderLayerBlocked())
        ResetRenderLayer();
	return ret;
}

bool ModuleRender::DrawSimpleRectangle(Rectangle bounds, Color tint)
{
    BeginTextureMode(layers.at(currentRenderLayer).data);
    if (IsCameraMode())
        BeginMode2D(camera);
    bool ret = true;
    DrawRectangle((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height, tint);
    if (IsCameraMode())
        EndMode2D();
    EndTextureMode();
    if (!IsRenderLayerBlocked())
        ResetRenderLayer();
    return ret;
}

bool ModuleRender::DrawSimpleCircle(Vector2 position, float radius, Color tint)
{
    BeginTextureMode(layers.at(currentRenderLayer).data);
    if (IsCameraMode())
        BeginMode2D(camera);
    bool ret = true;
    DrawCircle((int)position.x, (int)position.y, radius, tint);
    if (IsCameraMode())
        EndMode2D();
    EndTextureMode();
    if (!IsRenderLayerBlocked())
        ResetRenderLayer();
    return ret;
}

bool ModuleRender::DrawSimpleLine(Rectangle bounds,Color tint)
{
    BeginTextureMode(layers.at(currentRenderLayer).data);
    if (IsCameraMode())
        BeginMode2D(camera);
    bool ret = true;
    DrawLine((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height, tint);
    if (IsCameraMode())
        EndMode2D();
    EndTextureMode();
    if (!IsRenderLayerBlocked())
        ResetRenderLayer();
    return ret;
}

bool ModuleRender::DrawSimpleCircleLine(Vector2 position, float radius, Color tint)
{
    BeginTextureMode(layers.at(currentRenderLayer).data);
    if(IsCameraMode())
        BeginMode2D(camera);
    bool ret = true;
    DrawCircleLines((int)position.x, (int)position.y, radius, tint);
    if (IsCameraMode())
        EndMode2D();
    EndTextureMode();
    if (!IsRenderLayerBlocked())
        ResetRenderLayer();
    return ret;
}

bool ModuleRender::DrawText(const char* text, Vector2 position, Vector2 offset, Font font, int fontSize, int spacing, Color tint)
{
    BeginTextureMode(layers.at(currentRenderLayer).data);
    if(IsCameraModeAffectingText())
        BeginMode2D(camera);
    bool ret = true;
    position = { (float)position.x + offset.x, (float)position.y + offset.y };

    DrawTextEx(font, text, position, (float)fontSize, (float)spacing, tint);
    if (IsCameraModeAffectingText())
        EndMode2D();
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

void ModuleRender::SetCameraMode(bool status)
{
    cameraMode = status;
}

bool ModuleRender::IsCameraMode()
{
    return cameraMode;
}

void ModuleRender::SetCameraModeAffectText(bool status)
{
    cameraModeAffectsText = status;
}

bool ModuleRender::IsCameraModeAffectingText()
{
    return cameraMode && cameraModeAffectsText;
}

void ModuleRender::RenderLayerToScreen(Layer layer)
{
    Rectangle sourceRect = { 0, 0, (float)layer.data.texture.width, (float)-layer.data.texture.height };


    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float textureAspectRatio = abs(sourceRect.width / sourceRect.height);
    float screenAspectRatio = abs((float)screenWidth / (float)screenHeight);

    float targetWidth, targetHeight;

    if (textureAspectRatio > screenAspectRatio) {
        // Texture is wider than screen: fit by width
        targetWidth = (float)screenWidth;
        targetHeight = screenWidth / textureAspectRatio;
    }
    else {
        // Texture is taller than screen: fit by height
        targetHeight = (float)screenHeight;
        targetWidth = screenHeight * textureAspectRatio;
    }

    // Center the texture
    float offsetX = (screenWidth - targetWidth) / 2.0f;
    float offsetY = (screenHeight - targetHeight) / 2.0f;

    Rectangle destRect = { offsetX, offsetY, App->window->GetRealWidth(), App->window->GetRealHeight() };

    // Draw the layer's texture to the screen, flipping vertically
    DrawTexturePro(layer.data.texture, sourceRect, destRect, { 0, 0 }, 0, WHITE);
}

void ModuleRender::CreateLayer(RenderLayer layer)
{
    RenderTexture2D texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTextureFilter(texture.texture, TEXTURE_FILTER_POINT);
    layers.push_back({layer, texture});
}

void ModuleRender::CleanRenderLayer(Layer layer)
{
    BeginTextureMode(layer.data);
    ClearBackground(BLANK);
    EndTextureMode();
}
