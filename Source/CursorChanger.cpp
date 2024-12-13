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
		DisableCursor();
	else
		EnableCursor();
}

void CursorChanger::RenderCursor()
{
	if (IsTextureReady(texture)){
		Vector2 mousePos = GetMousePosition();
		DrawTexture(texture, mousePos.x, mousePos.y, WHITE);
		}
}
