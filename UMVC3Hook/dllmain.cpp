// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

#include "gui/dx9hook.h"
#include "gui/log.h"
#include "gui/notifications.h"

#include "plugin/Menu.h"
#include "plugin/Settings.h"
#include "plugin/Hooks.h"


#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"


using namespace Memory::VP;
// TODO: patterns


void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
	eLog::Message(__FUNCTION__, "INFO: UMVC3Hook Begin!");

	Notifications->Init();
	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));

	InjectHook(_addr(0x14001A490), tramp->Jump(CameraConstrutctor_Hook), PATCH_JUMP);

	// change dinput coop level
	Patch<char>(_addr(0x1406A9864) + 2, 0x14);

	CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(PluginProcess), 0, NULL, 0);
	HANDLE h = 0;

	h = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DX9Hook_Thread), 0, NULL, 0);

	if (!(h == nullptr)) CloseHandle(h);

}

bool CheckGame()
{
	char* gameName = (char*)(_addr(0x140B12D10));

	if (strcmp(gameName, "umvc3") == 0)
	{
		return true;
	}
	else
	{
		MessageBoxA(0, "Invalid game version!\nUMVC3Hook only supports latest (or it needs to be updated) Steam executable.", 0, MB_ICONINFORMATION);
		return false;
	}
}


extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		eLog::Initialize();

		if (CheckGame())
		{
			OnInitializeHook();
		}

	}
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		GUIImplementationDX9::Shutdown();
		break;
	}
	return TRUE;
}




