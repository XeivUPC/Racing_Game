#pragma once
#include "UIElement.h"

class UIButton : public UIElement
{

enum BUTTON_STATE {
	NORMAL,
	PRESSED,
	CLICKED
};

public:
	UIButton(Module* moduleAt);
	UIButton(Module* moduleAt, Vector2 position, Vector2 size);
	UIButton(Module* moduleAt, Vector2 position, Vector2 size, Texture2D* texture);
	UIButton(Module* moduleAt, Vector2 position, Vector2 size, Color color);

	~UIButton();

	void Update();
	void Render();

	BUTTON_STATE GetState();

protected:
	Texture2D* texture = nullptr;
	Color color = WHITE;

private:

	

	BUTTON_STATE state = NORMAL;
	bool isMouseOver = false;
};

