#pragma once
#include "umvc3.h"

class UMVC3Camera {
private:
	char pad[0x4C];
	float FOV;
	vector Pos; // 50
	char _pad[0x20];
	vector   Rotation;
public:
	void SetPosition(vector* pos);
	void SetRotation(vector* rot);


	void HookedSetPosition(vector* pos);
	void HookedSetRotation(vector* rot);
};