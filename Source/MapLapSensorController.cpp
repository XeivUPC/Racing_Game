#include "MapLapSensorController.h"
#include "Pilot.h"

void MapLapSensorController::CrossCheckpoint(Pilot* pilot, int checkpointOrder)
{
	if (checkpointOrder - 1 != pilot->CurrentCheckpoint())
		return;
}
