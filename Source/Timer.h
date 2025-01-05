#pragma once

#include "Globals.h"
#include "Timer.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Update();
	double ReadSec() const;

private:

    // Start time in seconds
	double timePassed;   
};