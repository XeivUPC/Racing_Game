#include "ModuleScene.h"
#include "Application.h"
#include "ModuleRender.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
    bool ret = true;

    return ret;
}

update_status ModuleScene::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
    return true;
}

void ModuleScene::StartFadeIn(ModuleScene* target, Color color, float time)
{
	if (doingFadeIn)
		return;

	fadeTarget = target;
	fadeColor = color;
	fadeTime = time;
	doingFadeIn = true;
	doingFadeOut = false;
	fadeTimer.Start();
	FadeIn();
}

void ModuleScene::StartFadeOut(Color color, float time)
{
	if (doingFadeOut)
		return;
	fadeTarget = nullptr;
	fadeColor = color;
	fadeTime = time;
	doingFadeOut = true;
	doingFadeIn = false;
	fadeTimer.Start();
	FadeOut();
}

void ModuleScene::FadeUpdate()
{
	EndMode2D();
	if (doingFadeIn)
		FadeIn();
	if (doingFadeOut)
		FadeOut();
	BeginMode2D(App->renderer->camera);
}

void ModuleScene::FadeIn()
{
	if (fadeTimer.ReadSec() >= fadeTime) {
		doingFadeIn = false;

		if (fadeTarget != nullptr)
		{
			if (fadeTarget != this) {
				fadeTarget->Enable();
			}
		}
		if (fadeTarget != this) {
			Disable();
		}
	}
	else {
		int opacity = (int)(255 * (fadeTimer.ReadSec() / fadeTime));
		if (opacity > 255)
			opacity = 255;
		Color color = { fadeColor.r,fadeColor.g,fadeColor.b,(unsigned char)opacity };
		DrawRectangle(0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, color);
	}
}

void ModuleScene::FadeOut()
{
	if (fadeTimer.ReadSec() < fadeTime) {

		int opacity = 255 - (int)(255 * (fadeTimer.ReadSec() / fadeTime));
		if (opacity < 0)
			opacity = 0;
		Color color = { fadeColor.r,fadeColor.g,fadeColor.b,(unsigned char)opacity };
		DrawRectangle(0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, color);
	}
	else {
		doingFadeOut = false;
	}
}
