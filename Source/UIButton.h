#pragma once
#include "UIElement.h"

class UIButton : public UIElement
{



public:

	enum BUTTON_STATE {
		NORMAL,
		OVER,
		PRESSED,
		CLICKED
	};

	UIButton(Module* moduleAt, Vector2 position, Vector2 size);

	~UIButton();

	BUTTON_STATE GetState();

private:
	BUTTON_STATE state = NORMAL;
};

