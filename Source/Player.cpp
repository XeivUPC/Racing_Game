#include "Player.h"
#include "Vehicle.h"
#include "Module.h"

Player::Player(Module* moduleat)
{
	moduleAt = moduleat;
	vehicle = new Vehicle(moduleat, "car-type1");
}

Player::~Player()
{
}

bool Player::Start()
{
	return true;
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

bool Player::Render()
{
	vehicle->Render();
	return true;
}

bool Player::CleanUp()
{
	vehicle->CleanUp();
	delete vehicle;
	return true;
}

Vector2 Player::GetVehiclePosition()
{
	return vehicle->GetPhysicPosition();
}
