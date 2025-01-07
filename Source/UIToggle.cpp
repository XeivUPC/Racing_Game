#include "UIToggle.h"
#include "Application.h"
#include <functional>

UIToggle::UIToggle(Module* moduleAt, Vector2 position, Vector2 size, bool status) : UIElement(moduleAt)
{
	bounds = { position.x, position.y, size.x, size.y };
	SetStatus(status);

	onMouseClick.emplace_back([this]() {SetStatus(!isOn); });
}

UIToggle::~UIToggle()
{
}

bool UIToggle::IsOn()
{
	return isOn;
}

void UIToggle::SetStatus(bool status)
{
	isOn = status;
	TriggerCallbacks(onValueChange, isOn);
}
