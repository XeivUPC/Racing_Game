#include "UIButton.h"
#include "ModuleRender.h"
#include "Application.h"
#include <functional>

UIButton::UIButton(Module* moduleAt, Vector2 position, Vector2 size) : UIElement(moduleAt)
{
	bounds = { position.x, position.y, size.x, size.y };
}

UIButton::UIButton(Module* moduleAt, Vector2 position, Vector2 size, Texture2D* texture) : UIButton(moduleAt, position, size)
{
	this->texture = texture;
}

UIButton::UIButton(Module* moduleAt, Vector2 position, Vector2 size, Color color) : UIButton(moduleAt, position, size)
{
	this->color = color;
}

UIButton::~UIButton()
{
}

void UIButton::Update()
{
	if (CheckCollisionPointRec(GetMousePosition(), bounds)) {	
		if (!isMouseOver) {
			if (onMouseEnter)
				onMouseEnter();
		}

		if (onMouseOver)
			onMouseOver();

		isMouseOver = true;

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			if(onMouseDown)
				onMouseDown();
			state = PRESSED;
		}
		else {

		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			if(onMouseClick)
				onMouseClick();
			state = CLICKED;
		}
		
	}
	else {
		if (isMouseOver) {
			if(onMouseExit)
				onMouseExit();
		}
		isMouseOver = false;
		state = NORMAL;
	}
}

UIButton::BUTTON_STATE UIButton::GetState()
{
	return state;
}
