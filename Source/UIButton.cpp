#include "UIButton.h"
#include "ModuleRender.h"
#include "Application.h"
#include <functional>

UIButton::UIButton(Module* moduleAt, Vector2 position, Vector2 size) : UIElement(moduleAt)
{
	bounds = { position.x, position.y, size.x, size.y };

	onMouseExit.emplace_back([this]() {state = NORMAL; });
	onMouseDown.emplace_back([this]() {state = PRESSED; });
	onMouseOver.emplace_back([this]() {if(state!=PRESSED)state = OVER; });
	onMouseClick.emplace_back([this]() {state = CLICKED; });
}

UIButton::~UIButton()
{
}

UIButton::BUTTON_STATE UIButton::GetState()
{
	return state;
}
