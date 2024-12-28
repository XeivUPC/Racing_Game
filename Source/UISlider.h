#pragma once
#include "UIElement.h"

class UIButton;

class UISlider : public UIElement
{
public:
	UISlider(Module* moduleAt, Vector2 position, Vector2 size);

	~UISlider();

	void Update();
	float GetValue();
	void SetValue(float valueToSet);
	Rectangle GetThumbBounds();
	bool IsThumbSelected();

	float minVal=0.f;
	float maxVal=1.f;

	std::vector<std::function<void(float)>> onValueChange;

private:
	void SelectThumb();
	void DeselectThumb();
	bool thumbSelected=false;
	
	float value = 0.f;
	UIButton* thumb;
};

