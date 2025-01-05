// ----------------------------------------------------
// j1Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"

#include "raylib.h"

Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	timePassed = 0;
}

void Timer::Update()
{
	timePassed += GetFrameTime();
}

double Timer::ReadSec() const
{
	return timePassed;
}