#include "Nitro.h"
#include "Timer.h"
#include "Module.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "Vehicle.h"

Nitro::Nitro(Module* ModuleAt, Vehicle* v)
{
	enabledTimer = new Timer();
	moduleAt = ModuleAt;
	vehicle = v;
}

Nitro::~Nitro()
{
}

void Nitro::Enable()
{
	if (!isEnabled)
	{
		if (currentSecondsEnabled > minSecondsToEnabled) {
			isEnabled = true;
			enabledTimer->Start();
		}
	}
}

void Nitro::Disable()
{
	isEnabled = false;
}

float Nitro::GetNitroMultiplier()
{
	if (isEnabled)return speedMultiplier;
	return 1.0f;
}

bool Nitro::IsEnabled()
{
	return isEnabled;
}

void Nitro::Update()
{
	
	if (isEnabled)
	{
		currentSecondsEnabled -= GetFrameTime()*4;
		if (currentSecondsEnabled <= 0.0f)
		{
			currentSecondsEnabled = 0;
			Disable();
		}
	}
	else
	{
		if(currentSecondsEnabled < maxSecondsEnabled)
			currentSecondsEnabled += GetFrameTime();
		else
		{
			currentSecondsEnabled == maxSecondsEnabled;
		}
	}
}

void Nitro::Render()
{
	moduleAt->App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
	if (currentSecondsEnabled < maxSecondsEnabled)
	{
		if (currentSecondsEnabled < minSecondsToEnabled && !isEnabled) {
			moduleAt->App->renderer->DrawSimpleRectangle({ vehicle->body->GetPhysicPosition().x - currentSecondsEnabled * 10 / 2,vehicle->body->GetPhysicPosition().y + 50,currentSecondsEnabled * 10, 5 }, RED);

		}else
			moduleAt->App->renderer->DrawSimpleRectangle({vehicle->body->GetPhysicPosition().x-currentSecondsEnabled*10/2,vehicle->body->GetPhysicPosition().y + 50,currentSecondsEnabled *10, 5}, SKYBLUE);
	}
	moduleAt->App->renderer->UnlockRenderLayer();
}

void Nitro::CleanUp()
{
	delete enabledTimer;
}
