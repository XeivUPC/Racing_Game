#include "GamePositionsDisplayer.h"
#include "Pilot.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "SceneGame.h"
#include "Application.h"
#include "ModuleAssetLoader.h"

GamePositionsDisplayer::GamePositionsDisplayer(SceneGame* GameAt)
{
	gameAt = GameAt;
	texture = gameAt->App->texture->GetTexture("Characters");
}

GamePositionsDisplayer::~GamePositionsDisplayer()
{
}

void GamePositionsDisplayer::Render()
{
	Vector2 anchor = { 0,225 };

	vector<Pilot*>pilots = gameAt->GetRacePlacePositions();
	Rectangle rect = { 0,0,48,48 };
	gameAt->App->renderer->SetCameraMode(false);
	gameAt->App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_1);

	gameAt->App->renderer->DrawSimpleRectangle({ anchor.x,anchor.y, 140, 50.f*pilots.size()}, {0,0,0,175});
	for (size_t i = 0; i < pilots.size(); i++)
	{
		rect.x = rect.width * (pilots[i]->characterIndex);
		Vector2 slotAnchor = { 10,anchor.y + 50 * i +8};

		Vector2 iconPosition = { slotAnchor.x + 20, slotAnchor.y};
		gameAt->App->renderer->Draw(*texture, iconPosition, {0,0}, &rect, 0, 0.7f);
	

		string text = to_string(i + 1);
		Vector2 textSize = MeasureTextEx(gameAt->App->assetLoader->agencyB, text.c_str(), 20, 0);
		Vector2 positionPosition = { slotAnchor.x, slotAnchor.y + textSize.y / 2 };
		gameAt->App->renderer->DrawText(text.c_str(), positionPosition, { 0,0 }, gameAt->App->assetLoader->agencyB, 20, 0, WHITE);


		text = pilots[i]->GetPilotName();
		textSize = MeasureTextEx(gameAt->App->assetLoader->agencyB, text.c_str(), 20, 0);
		Vector2 namePosition = { slotAnchor.x + 60, slotAnchor.y + textSize.y / 2 };
		gameAt->App->renderer->DrawText(text.c_str(), namePosition, {0,0}, gameAt->App->assetLoader->agencyB, 20, 0, WHITE);
	}
	gameAt->App->renderer->UnlockRenderLayer();
	gameAt->App->renderer->SetCameraMode(true);
}

