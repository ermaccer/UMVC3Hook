#pragma once
#include "..\utils.h"
#include "..\umvc3\Camera.h"
#include "..\umvc3\Vector.h"

int64 CameraConstrutctor_Hook(int64 camera, int64 a2);
void PluginProcess();