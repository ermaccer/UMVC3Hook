#include "UMVC3Camera.h"
#include "umvc3menu.h"
#include <iostream>
void UMVC3Camera::SetPosition(vector * pos)
{
	((void(__fastcall*)(UMVC3Camera*, vector*))_addr(0x14000BF40))(this, pos);
}

void UMVC3Camera::SetRotation(vector * rot)
{
	((void(__fastcall*)(UMVC3Camera*, vector*))_addr(0x14000BF40))(this, rot);
}

void UMVC3Camera::HookedSetPosition(vector * pos)
{
	if (TheMenu->m_bCustomCameraFOV)
		SetCamFOV(TheMenu->camFov);
	else
		TheMenu->camFov = GetCamFOV();

	if (!TheMenu->m_bCustomCameraPos)
	{
		TheMenu->camPos = *pos;
		SetPosition(pos);
	}
	else
		SetPosition(&TheMenu->camPos);
}

void UMVC3Camera::HookedSetRotation(vector * rot)
{
	if (!TheMenu->m_bCustomCameraRot)
	{
		TheMenu->camRot = *rot;
		SetRotation(rot);
	}
	else
		SetRotation(&TheMenu->camRot);
}
