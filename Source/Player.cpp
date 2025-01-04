#include "Player.h"
#include "Vehicle.h"
#include "SceneGame.h"
#include <string>

Player::Player(SceneGame* gameAt, RaceTrack* track, std::string vehicleType) : Pilot(gameAt, track, vehicleType)
{

}

Player::~Player()
{
}

update_status Player::Update()
{
	Vector2 moveInput = { 0,0 };

	if (IsKeyDown(KEY_W))
		moveInput.y += 1;
	if (IsKeyDown(KEY_S))
		moveInput.y -= 1;

	if (IsKeyDown(KEY_A))
		moveInput.x -= 1;
	if (IsKeyDown(KEY_D))
		moveInput.x += 1;

	vehicle->SetInput(moveInput);
	vehicle->Update();

	

	return UPDATE_CONTINUE;
}
