#include "Camera.h"
UMVC3GameCamera* TheCamera = nullptr;

UMVC3MainCamera* GetMainCamera()
{
	int64 cam_ptr = *(int64*)(0x140E17930);
	if (cam_ptr)
		return (UMVC3MainCamera*)(cam_ptr + 0x50);
	return nullptr;
}