#include "Player.h"
#include "Vehicle.h"
#include "SceneGame.h"
#include <string>
#include "Nitro.h"

Player::Player(SceneGame* gameAt, RaceTrack* track, std::string vehicleType, Color vehicleColor) : Pilot(gameAt, track, vehicleType, vehicleColor)
{
	pilotName = "Player";
	characterIndex = 0;
}

Player::~Player()
{
}

update_status Player::Update()
{
	Pilot::Update();
	if (!exploded) {
		Vector2 moveInput = { 0,0 };

		if (IsKeyDown(KEY_W))
			moveInput.y += 1;
		if (IsKeyDown(KEY_S))
			moveInput.y -= 1;

		if (IsKeyDown(KEY_A))
			moveInput.x -= 1;
		if (IsKeyDown(KEY_D))
			moveInput.x += 1;
		if (IsKeyDown(KEY_SPACE))
			vehicle->nitro->Enable();
		else
			vehicle->nitro->Disable();

		vehicle->SetInput(moveInput);
		vehicle->Update();
	}

	

	return UPDATE_CONTINUE;
}
