#include "Player.h"
#include "Vehicle.h"
#include "Module.h"
#include <string>

Player::Player(Module* moduleat, std::string vehicleType) : Pilot(moduleat, vehicleType)
{
}

Player::~Player()
{
}

bool Player::Update()
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
	return true;
}
