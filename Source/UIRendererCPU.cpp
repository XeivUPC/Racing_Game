#include "UIRendererCPU.h"
#include "Pilot.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "SceneGame.h"
#include "Application.h"
#include "ModuleAssetLoader.h"

UIRendererCPU::UIRendererCPU(SceneGame* GameAt)
{
	gameAt = GameAt;
	texture = gameAt->App->texture->GetTexture("Characters");
}

UIRendererCPU::~UIRendererCPU()
{
}

void UIRendererCPU::Render()
{
	vector<Pilot*>pilots = gameAt->GetRacePlacePositions();
	Rectangle rect = { 0,0,48,48 };
	gameAt->App->renderer->SetCameraMode(false);
	gameAt->App->renderer->DrawSimpleRectangle({0,180, 125, 50.f*pilots.size()}, {0,0,0,125});
	for (size_t i = 0; i < pilots.size(); i++)
	{
		rect.x = 48 * (pilots[i]->characterIndex);

		gameAt->App->renderer->Draw(*texture, {30, 190.f + 50*i}, {0,0}, &rect, 0, 0.5f);
		Vector2 textSize = MeasureTextEx(gameAt->App->assetLoader->agencyB, to_string(i+1).c_str(), 20, 0);
		gameAt->App->renderer->DrawText(to_string(i+1).c_str(), { 10, 200.f + 50 * i + textSize.y / 2 -24*0.5f}, { 0,0 }, gameAt->App->assetLoader->agencyB, 20, 0, WHITE);
		textSize = MeasureTextEx(gameAt->App->assetLoader->agencyB, pilots[i]->GetPilotName().c_str(), 20, 0);
		gameAt->App->renderer->DrawText(pilots[i]->GetPilotName().c_str(), {60, 200.f + 50 * i+ textSize.y/2 - 24 * 0.5f }, {0,0}, gameAt->App->assetLoader->agencyB,20,0,WHITE);
	}
	gameAt->App->renderer->SetCameraMode(true);
}

