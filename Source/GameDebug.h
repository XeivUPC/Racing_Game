#pragma once
#include "Application.h"
#include "SceneGame.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "Box2DFactory.h"
#include "ModuleWindow.h"
#include "Pilot.h"
#include "Vehicle.h"


class PhysBody;
class PhysJoint;
class GameDebug

{
public:
	GameDebug(SceneGame* gameAt) {
		this->gameAt = gameAt;
	}
	~GameDebug() {
		if (mouseJoint != nullptr)
			delete mouseJoint;
	};
	void Update() {
		if (!gameAt->App->physics->IsDebugActive()) {
			if (mouseJoint != nullptr) {
				delete mouseJoint;
				mouseJoint = nullptr;
			}
			return;
		}
		if (IsMouseButtonPressed(0) && mouseJoint == nullptr) {
			for (size_t i = 0; i < gameAt->pilots.size(); i++)
			{
				Rectangle bounds = gameAt->pilots[i]->vehicle->GetBounds();
				Vector2 origin = { bounds.x, bounds.y };
				float angle = gameAt->pilots[i]->vehicle->body->GetAngle();

				Vector2 points[4] = {
				{bounds.x - bounds.width / 2, bounds.y - bounds.height / 2},
				{bounds.x + bounds.width / 2, bounds.y - bounds.height / 2},
				{bounds.x + bounds.width / 2, bounds.y + bounds.height / 2},
				{bounds.x - bounds.width / 2, bounds.y + bounds.height / 2}
				};

				auto RotatePoint = [](Vector2 point, Vector2 origin, float angle) {
					float cosine = cos(angle);
					float sine = sin(angle);

					// Translate point back to origin, rotate, and translate back
					float dx = point.x - origin.x;
					float dy = point.y - origin.y;

					float newX = dx * cosine - dy * sine + origin.x;
					float newY = dx * sine + dy * cosine + origin.y;

					return Vector2{ newX, newY };
					};

				for (int j = 0; j < 4; j++) {
					points[j] = RotatePoint(points[j], origin, angle);  // Rotate the points
				}

				Vector2 mousePos = GetScreenToWorld2D(gameAt->App->window->GetVirtualMousePos(), gameAt->App->renderer->camera);
				if (CheckCollisionPointPoly(mousePos, points, 4)) {
					ModulePhysics* physics = gameAt->App->physics;
					const Box2DFactory& factory = physics->factory();
					mouseJoint = factory.CreateMouseJoint(gameAt->pilots[i]->vehicle->body, gameAt->App->physics->ground, { PIXEL_TO_METERS(mousePos.x), PIXEL_TO_METERS(mousePos.y) }, 100000 * gameAt->pilots[i]->vehicle->body->GetMass(), 100, 0.2);
					break;
				}

			}
		}
		else if (IsMouseButtonDown(0) && mouseJoint != nullptr) {
			Vector2 mousePos = GetScreenToWorld2D(gameAt->App->window->GetVirtualMousePos(), gameAt->App->renderer->camera);
			mousePos = { PIXEL_TO_METERS(mousePos.x), PIXEL_TO_METERS(mousePos.y) };
			mouseJoint->SetTarget(mousePos);
		}
		else if (IsMouseButtonReleased(0) && mouseJoint != nullptr) {
			delete mouseJoint;
			mouseJoint = nullptr;
		}
	}

private:
	SceneGame* gameAt = nullptr;
	PhysJoint* mouseJoint = nullptr;
};