#include "MapLapSensorController.h"
#include "Pilot.h"
#include "SceneGame.h"
#include "RaceTrack.h"

MapLapSensorController::MapLapSensorController(SceneGame* sgame)
{
	game = sgame;
}

MapLapSensorController::~MapLapSensorController()
{
}


void MapLapSensorController::CrossCheckpoint(Pilot* pilot, int checkpointOrder)
{
	if (checkpointOrder - 1 != pilot->CurrentCheckpoint())
		return;
	pilot->AddCheckpoint();
	if (pilot->CurrentCheckpoint() == game->track->GetTrackSensors().size())
		pilot->AddLap();
}

bool MapLapSensorController::CleanUp()
{
	return true;
}
