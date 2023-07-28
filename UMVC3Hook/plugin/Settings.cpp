#include "Settings.h"
#include "../utils/IniReader.h"
#include <Windows.h>
eSettingsManager* SettingsMgr = new eSettingsManager;

eSettingsManager::eSettingsManager()
{
	CIniReader ini("");
	CIniReader user("umvc3hook_user.ini");


	bEnableConsoleWindow = ini.ReadBoolean("Settings", "bEnableConsoleWindow", true);


	iHookMenuOpenKey = user.ReadInteger("Settings", "iHookMenuOpenKey", -1);
	if (iHookMenuOpenKey == -1) iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);

	iToggleFreeCameraKey = user.ReadInteger("Settings", "iToggleFreeCameraKey", -1);
	if (iToggleFreeCameraKey == -1) iToggleFreeCameraKey = 0;

	iToggleHUDKey = user.ReadInteger("Settings", "iToggleHUDKey", -1);
	if (iToggleHUDKey == -1) iToggleHUDKey = 0;

	iFreeCameraKeyFOVPlus = user.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", -1);
	if (iFreeCameraKeyFOVPlus == -1) iFreeCameraKeyFOVPlus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0);

	iFreeCameraKeyFOVMinus = user.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", -1);
	if (iFreeCameraKeyFOVMinus == -1) iFreeCameraKeyFOVMinus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0);

	iFreeCameraKeyXPlus = user.ReadInteger("Settings", "iFreeCameraKeyXPlus", -1);
	if (iFreeCameraKeyXPlus == -1) iFreeCameraKeyXPlus = ini.ReadInteger("Settings", "iFreeCameraKeyXPlus", 0);

	iFreeCameraKeyXMinus = user.ReadInteger("Settings", "iFreeCameraKeyXMinus", -1);
	if (iFreeCameraKeyXMinus == -1) iFreeCameraKeyXMinus = ini.ReadInteger("Settings", "iFreeCameraKeyXMinus", 0);

	iFreeCameraKeyYPlus = user.ReadInteger("Settings", "iFreeCameraKeyYPlus", -1);
	if (iFreeCameraKeyYPlus == -1) iFreeCameraKeyYPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYPlus", 0);

	iFreeCameraKeyYMinus = user.ReadInteger("Settings", "iFreeCameraKeyYMinus", -1);
	if (iFreeCameraKeyYMinus == -1) iFreeCameraKeyYMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYMinus", 0);

	iFreeCameraKeyZPlus = user.ReadInteger("Settings", "iFreeCameraKeyZPlus", -1);
	if (iFreeCameraKeyZPlus == -1) iFreeCameraKeyZPlus = ini.ReadInteger("Settings", "iFreeCameraKeyZPlus", 0);

	iFreeCameraKeyZMinus = user.ReadInteger("Settings", "iFreeCameraKeyZMinus", -1);
	if (iFreeCameraKeyZMinus == -1) iFreeCameraKeyZMinus = ini.ReadInteger("Settings", "iFreeCameraKeyZMinus", 0);

	iFreeCameraKeyYawPlus = user.ReadInteger("Settings", "iFreeCameraKeyYawPlus", -1);
	if (iFreeCameraKeyYawPlus == -1) iFreeCameraKeyYawPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYawPlus", 0);

	iFreeCameraKeyYawMinus = user.ReadInteger("Settings", "iFreeCameraKeyYawMinus", -1);
	if (iFreeCameraKeyYawMinus == -1) iFreeCameraKeyYawMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYawMinus", 0);

	iFreeCameraKeyRollPlus = user.ReadInteger("Settings", "iFreeCameraKeyRollPlus", -1);
	if (iFreeCameraKeyRollPlus == -1) iFreeCameraKeyRollPlus = ini.ReadInteger("Settings", "iFreeCameraKeyRollPlus", 0);

	iFreeCameraKeyRollMinus = user.ReadInteger("Settings", "iFreeCameraKeyRollMinus", -1);
	if (iFreeCameraKeyRollMinus == -1) iFreeCameraKeyRollMinus = ini.ReadInteger("Settings", "iFreeCameraKeyRollMinus", 0);


	iFreeCameraKeyPitchPlus = user.ReadInteger("Settings", "iFreeCameraKeyPitchPlus", -1);
	if (iFreeCameraKeyPitchPlus == -1) iFreeCameraKeyPitchPlus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchPlus", 0);

	iFreeCameraKeyPitchMinus = user.ReadInteger("Settings", "iFreeCameraKeyPitchMinus", -1);
	if (iFreeCameraKeyPitchMinus == -1) iFreeCameraKeyPitchMinus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchMinus", 0);

	fMenuScale = user.ReadFloat("MenuSettings", "fMenuScale", 1.0f);

	if (fMenuScale < 1.0f)
		fMenuScale = 1.0f;

}

void eSettingsManager::SaveSettings()
{
	CIniReader user("umvc3hook_user.ini");
	user.WriteFloat("MenuSettings", "fMenuScale", fMenuScale);

	user.WriteInteger("Settings", "iHookMenuOpenKey", iHookMenuOpenKey);
	user.WriteInteger("Settings", "iFreeCameraKeyXPlus", iFreeCameraKeyXPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyXMinus", iFreeCameraKeyXMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyYPlus", iFreeCameraKeyYPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyYMinus", iFreeCameraKeyYMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyZPlus", iFreeCameraKeyZPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyZMinus", iFreeCameraKeyZMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyYawPlus", iFreeCameraKeyYawPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyYawMinus", iFreeCameraKeyYawMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyRollPlus", iFreeCameraKeyRollPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyRollMinus", iFreeCameraKeyRollMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyPitchPlus", iFreeCameraKeyPitchPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyPitchMinus", iFreeCameraKeyPitchMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyFOVPlus", iFreeCameraKeyFOVPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyFOVMinus", iFreeCameraKeyFOVMinus);
	user.WriteInteger("Settings", "iToggleFreeCameraKey", iToggleFreeCameraKey);
	user.WriteInteger("Settings", "iToggleHUDKey", iToggleHUDKey);


	CIniReader ini("");
	ini.WriteBoolean("Settings", "bEnableConsoleWindow", bEnableConsoleWindow);
}

void eSettingsManager::ResetKeys()
{
	iHookMenuOpenKey = VK_F1;
	iToggleFreeCameraKey = 0;
	iToggleHUDKey = 0;
	iFreeCameraKeyXPlus = 104;
	iFreeCameraKeyXMinus = 98;
	iFreeCameraKeyYPlus = 102;
	iFreeCameraKeyYMinus = 100;
	iFreeCameraKeyZPlus = 103;
	iFreeCameraKeyZMinus = 97;
	iFreeCameraKeyYawPlus = 39;
	iFreeCameraKeyYawMinus = 37;
	iFreeCameraKeyPitchPlus = 38;
	iFreeCameraKeyPitchMinus = 40;
	iFreeCameraKeyRollMinus = 99;
	iFreeCameraKeyRollPlus = 105;
	iFreeCameraKeyFOVPlus = 107;
	iFreeCameraKeyFOVMinus = 109;
}
