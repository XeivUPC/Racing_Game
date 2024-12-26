#include "UISlider.h"
#include "UIButton.h"

UISlider::UISlider(Module* moduleAt, Vector2 position, Vector2 size) : UIElement(moduleAt)
{
	bounds = { position.x, position.y, size.x, size.y };

	Vector2 thumbSize = {20,20};
	Vector2 thumbPos = {position.x - thumbSize.x/2.f ,position.y - thumbSize.y /2.f + size.y / 2 };
	thumb = new UIButton(moduleAt, thumbPos, thumbSize);

	thumb->onMouseDown = [&]() {SelectThumb();};
}

UISlider::~UISlider()
{
	delete thumb;
}

void UISlider::Update()
{
	thumb->Update();
	if (thumbSelected)
	{
		Vector2 mousePos = GetMousePosition();
		Vector2 moveBounds = { bounds.x - thumb->bounds.width / 2.f , bounds.x + bounds.width - thumb->bounds.width / 2.f };

		if (mousePos.x < moveBounds.x)
			mousePos.x = moveBounds.x;
		if (mousePos.x > moveBounds.y)
			mousePos.x = moveBounds.y;

		thumb->bounds.x = mousePos.x;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			DeselectThumb();
	}
}
\

float UISlider::GetValue()
{
	Vector2 moveBounds = { bounds.x - thumb->bounds.width / 2 , bounds.x + bounds.width - thumb->bounds.width / 2 };

	return minVal + (thumb->bounds.x - moveBounds.x) * (maxVal - minVal) / (moveBounds.y - moveBounds.x);
}

float UISlider::SetValue()
{
	Vector2 moveBounds = { bounds.x - thumb->bounds.width / 2 , bounds.x + bounds.width - thumb->bounds.width / 2 };
	return moveBounds.x + (value - minVal) * (moveBounds.y - moveBounds.x) / (maxVal - minVal);
}

Rectangle UISlider::GetThumbBounds()
{
	return thumb->bounds;
}

bool UISlider::IsThumbSelected()
{
	return thumbSelected;
}

void UISlider::SelectThumb()
{
	thumbSelected = true;
}

void UISlider::DeselectThumb()
{
	thumbSelected = false;
}
