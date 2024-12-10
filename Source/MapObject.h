#pragma once
#include "ModuleGame.h"

class MapObject
{
public:
	MapObject(ModuleGame* gameAt):  gameAt(gameAt) 
	{}

	virtual ~MapObject() 
	{}

	ModuleGame* GetGameAt() {
		return gameAt;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

protected:
	ModuleGame* gameAt = nullptr;
	Vector2 position = { 0,0 };
};

