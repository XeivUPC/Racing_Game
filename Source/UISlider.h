#pragma once
#include "UIElement.h"

class UIButton;

class UISlider : public UIElement
{
public:
	UISlider(Module* moduleAt, Vector2 position, Vector2 size);

	~UISlider();

	void Update();
	void Render();
	float GetValue();
	float SetValue();

	float minVal=0.f;
	float maxVal=1.f;

	UIButton* thumb;

protected:
	Texture2D* texture = nullptr;
	Color color = WHITE;

private:
	void SelectThumb();
	void DeselectThumb();
	bool thumbSelected;
	
	float value = 0.f;
};

