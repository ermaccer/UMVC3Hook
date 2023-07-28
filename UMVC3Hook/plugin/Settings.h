#pragma once
#include <Windows.h>

struct eMouseSettings {
	int sens;
	bool invert_y;
	bool invert_x;
};


class eSettingsManager {
public:
	eSettingsManager();

	bool bEnableConsoleWindow;
	bool bEnableGamepadSupport;


	// generic
	int iHookMenuOpenKey;
	int iToggleFreeCameraKey;
	int iToggleHUDKey;

	// free camera keys
	int iFreeCameraKeyXPlus;
	int iFreeCameraKeyXMinus;
	int iFreeCameraKeyYPlus;
	int iFreeCameraKeyYMinus;
	int iFreeCameraKeyZPlus;
	int iFreeCameraKeyZMinus;


	int iFreeCameraKeyYawPlus;
	int iFreeCameraKeyYawMinus;

	int iFreeCameraKeyPitchPlus;
	int iFreeCameraKeyPitchMinus;

	int iFreeCameraKeyRollMinus;
	int iFreeCameraKeyRollPlus;



	int iFreeCameraKeyFOVPlus;
	int iFreeCameraKeyFOVMinus;

	eMouseSettings mouse;

	float fMenuScale;

	void SaveSettings();
	void ResetKeys();
};

extern eSettingsManager* SettingsMgr;