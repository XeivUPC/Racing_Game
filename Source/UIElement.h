#pragma once
#include "Module.h"
#include <functional>

class UIElement
{
public:
	UIElement(Module* moduleAt) {
		this->moduleAt = moduleAt;
	}
	~UIElement() {};

	virtual void Update() {};

	/// <summary>
	/// In Order to add function to one of this actions, add the following line
	/// uiElement->onMouseEvent = [&]() {FunctionName();};
	/// 
	/// Event is Over, Enter, Exit, ...
	/// The function must return void, and no args
	/// </summary>

	std::function<void(void)> onMouseOver;
	std::function<void(void)> onMouseEnter;
	std::function<void(void)> onMouseExit;
	std::function<void(void)> onMouseDown;
	std::function<void(void)> onMouseClick;

	Rectangle bounds{0,0,0,0}; //// x - y - width - height
protected:

	Module* moduleAt = nullptr;
};

