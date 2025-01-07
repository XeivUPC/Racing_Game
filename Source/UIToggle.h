#pragma once
#include "UIElement.h"

class UIToggle : public UIElement
{



public:

	UIToggle(Module* moduleAt, Vector2 position, Vector2 size, bool status);

	~UIToggle();

	bool IsOn();
	void SetStatus(bool status);

	std::vector<std::function<void(float)>> onValueChange;

private: 
	bool isOn = false;
};
