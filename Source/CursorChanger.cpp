#include "CursorChanger.h"

CursorChanger::CursorChanger()
{
	
}

CursorChanger::~CursorChanger()
{
	if (IsTextureReady(texture))
		UnloadTexture(texture);
}

void CursorChanger::SetCursor(std::string path)
{
	if(IsTextureReady(texture))
		UnloadTexture(texture);
	texture = LoadTexture(path.c_str());

	if (IsTextureReady(texture))
		HideCursor();
	else
		ShowCursor();
}

void CursorChanger::RenderCursor()
{
	if (IsTextureReady(texture)){
		Vector2 mousePos = GetMousePosition();
		DrawTexture(texture, (int)mousePos.x, (int)mousePos.y, WHITE);
		}
}
