#pragma once
#include "umvc3.h"

class UMVC3Menu {
public:
	bool m_bIsActive;
	bool m_bIsFocused;
	bool m_bCustomCameraPos;
	bool m_bCustomCameraFOV;
	bool m_bCustomCameraRot;
	bool m_bFreeCam;

	int  m_nFreeCameraSpeed;
	int  m_nFreeCameraRotationSpeed;

	vector camPos;
	vector camRot;
	float  camFov;

	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();
	bool GetActiveState();
};

char* GetUMVC3HookVersion();
extern UMVC3Menu* TheMenu;