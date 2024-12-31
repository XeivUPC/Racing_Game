#pragma once

class Vehicle;
class Module;
class Vector2;

class Player
{
public:
	Player(Module* moduleat);
	~Player();
	bool Start();
	bool Update();
	bool Render();
	bool CleanUp();
	Vector2 GetVehiclePosition();
private:
	Vehicle* vehicle;
	Module* moduleAt;
};