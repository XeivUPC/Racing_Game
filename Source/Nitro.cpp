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
		isEnabled = true;
		enabledTimer->Start();
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
	enabledTimer->Update();
	if (isEnabled)
	{
		currentSecondsEnabled -= enabledTimer->ReadSec();
		if (currentSecondsEnabled <= 0.0f)
		{
			currentSecondsEnabled = 0;
			Disable();
		}
	}
	else
	{
		if(currentSecondsEnabled < maxSecondsEnabled)
			currentSecondsEnabled += enabledTimer->ReadSec()/50;
		else
		{
			currentSecondsEnabled == maxSecondsEnabled;
		}
	}
}

void Nitro::Render()
{
	moduleAt->App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);
	if(currentSecondsEnabled < maxSecondsEnabled)
		moduleAt->App->renderer->DrawSimpleRectangle({vehicle->body->GetPhysicPosition().x-currentSecondsEnabled*10/2,vehicle->body->GetPhysicPosition().y + 50,currentSecondsEnabled *10, 5}, SKYBLUE);
	moduleAt->App->renderer->UnlockRenderLayer();
}

void Nitro::CleanUp()
{
	delete enabledTimer;
}
