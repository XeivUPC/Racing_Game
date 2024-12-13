#pragma once
#include <raylib.h>
#include <string>

class CursorChanger
{
public:
	CursorChanger();
	~CursorChanger();

	void SetCursor(std::string path);
	void RenderCursor();
private:
	Texture2D texture;
};

