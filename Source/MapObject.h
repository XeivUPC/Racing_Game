#pragma once
#include "Module.h"

class MapObject
{
public:
	MapObject(Module* moduleAt):  moduleAt(moduleAt) 
	{}

	virtual ~MapObject() 
	{}

	Module* GetModuleAt() {
		return moduleAt;
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
	Module* moduleAt = nullptr;
	Vector2 position = { 0,0 };
};

