#pragma once
#include "Module.h"
#include <functional>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

class UIElement

{
public:
	UIElement(Module* moduleAt) {
		this->moduleAt = moduleAt;
	}
	~UIElement() {};

	virtual void Update() {
		Vector2 mousePos = moduleAt->App->window->GetVirtualMousePos();
		bool mouseInside = CheckCollisionPointRec(mousePos, bounds);

		if (mouseInside && !isMouseOver && canBeInteracted) {
			TriggerCallbacks(onMouseEnter);
			isMouseOver = true;
		}
		else if(!mouseInside && isMouseOver || !canBeInteracted){
			TriggerCallbacks(onMouseExit);
			isMouseOver = false;
		}

		if (mouseInside && canBeInteracted) {
			TriggerCallbacks(onMouseOver);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				TriggerCallbacks(onMouseDown);
				canBeClicked = true;
			}

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				TriggerCallbacks(onMouseUp);
				if(canBeClicked)
					TriggerCallbacks(onMouseClick);
			}
		}
		else {
			canBeClicked = false;
		}
	
	};

	virtual void CanBeInteracted(bool status) {
		canBeInteracted = status;
	}

	/// <summary>
	/// In Order to add function to one of this actions, add the following line
	/// uiElement->onMouseEvent = [&]() {FunctionName();};
	/// 
	/// Event is Over, Enter, Exit, ...
	/// The function must return void, and no args
	/// </summary>


	std::vector<std::function<void()>> onMouseOver;
	std::vector<std::function<void()>> onMouseEnter;
	std::vector<std::function<void()>> onMouseExit;
	std::vector<std::function<void()>> onMouseDown;
	std::vector<std::function<void()>> onMouseUp;
	std::vector<std::function<void()>> onMouseClick;

	Rectangle bounds{0,0,0,0}; //// x - y - width - height

protected:

	Module* moduleAt = nullptr;

	bool isMouseOver=false;
	bool canBeClicked = false;


	bool canBeInteracted = true;

	void TriggerCallbacks(std::vector<std::function<void()>>& callbacks) {

		for (auto& callback : callbacks) {
			callback();
		}
	}

	void TriggerCallbacks(std::vector<std::function<void(int)>>& callbacks, int value) {
		for (auto& callback : callbacks) {
			callback(value);
		}
	}

	void TriggerCallbacks(std::vector<std::function<void(float)>>& callbacks, float value) {
		for (auto& callback : callbacks) {
			callback(value);
		}
	}
};

