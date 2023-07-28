#include "Menu.h"
#include "Settings.h"

#include "../gui/notifications.h"
#include "../gui/imgui/imgui.h"

#include "../umvc3/Camera.h"

UMVC3Menu* TheMenu = new UMVC3Menu();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

UMVC3Menu::UMVC3Menu()
{
}

void UMVC3Menu::OnActivate()
{
	m_bIsActive ^= 1;
}

void UMVC3Menu::OnToggleFreeCamera()
{
	if (m_bIsActive)
		return;

	m_bFreeCam ^= 1;
}

void UMVC3Menu::OnToggleHUD()
{
	if (m_bIsActive)
		return;

	m_bDisableHUD ^= 1;
}

void UMVC3Menu::Draw()
{
	if (!m_bIsActive)
		return;

	ImGui::GetIO().MouseDrawCursor = true;

	ImGui::Begin("UMVC3Hook by ermaccer", &m_bIsActive, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SM_Settings] = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::BeginMenu("About"))
			{
				ImGui::MenuItem("Version: " UMVC3HOOK_VERSION);
				ImGui::MenuItem("Date: " __DATE__);
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

	}
	ImGui::EndMenuBar();

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Camera"))
		{
			DrawCameraTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			DrawMiscTab();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();


	if (m_bSubmenuActive[SM_Settings])
		DrawSettings();

}

void UMVC3Menu::Process()
{

	Memory::VP::Patch<char>(_addr(0x140532D80), m_bFreeCam ? 0xC3 : 0x48);

	Memory::VP::Patch<char>(_addr(0x140326A70), (m_bDisableHUD || m_bDisableHUDTotal) ? 0xC3 : 0x48);
	Memory::VP::Patch<char>(_addr(0x140324240), (m_bDisableHUD || m_bDisableHUDTotal) ? 0xC3 : 0x48);
	Memory::VP::Patch<char>(_addr(0x1404537B0), m_bDisableHUDTotal ? 0xC3 : 0x48);

	Memory::VP::Patch<char>(_addr(0x14077EA40), m_bDisableEffects ? 0xC3 : 0x48);
	Memory::VP::Patch<char>(_addr(0x14077D330), m_bDisableEffects ? 0xC3 : 0x48);

	UpdateControls();
	UpdateFreecam();
}

void UMVC3Menu::UpdateControls()
{

}

void UMVC3Menu::UpdateFreecam()
{

	UMVC3MainCamera* cam = GetMainCamera();

	if (!cam)
		return;

	Vector fwd = cam->mat.forward;
	Vector up = cam->mat.up;
	Vector right = cam->mat.right;

	static XMVECTOR defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	static XMVECTOR defaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	static XMVECTOR defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	float delta = GUIImplementationDX9::GetDeltaTime();

	if (m_bFreeCam)
	{
		// forward

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camMat.pos.X += TheMenu->m_fFreeCameraSpeed * delta * 1;


		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camMat.pos.X += TheMenu->m_fFreeCameraSpeed * delta * -1;

		// right

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camMat.pos.Y += TheMenu->m_fFreeCameraSpeed * delta * 1;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camMat.pos.Y += TheMenu->m_fFreeCameraSpeed * delta * -1;

		// up

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camMat.pos.Z += TheMenu->m_fFreeCameraSpeed * delta * 1;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camMat.pos.Z += TheMenu->m_fFreeCameraSpeed * delta * -1;


		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			camRot.X += TheMenu->m_fFreeCameraRotationSpeed * delta;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			camRot.X -= TheMenu->m_fFreeCameraRotationSpeed * delta;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			camRot.Y += TheMenu->m_fFreeCameraRotationSpeed * delta;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			camRot.Y -= TheMenu->m_fFreeCameraRotationSpeed * delta;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			camRot.Z += TheMenu->m_fFreeCameraRotationSpeed * delta;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			camRot.Z -= TheMenu->m_fFreeCameraRotationSpeed * delta;
	}

	if (m_bFreeCam || m_bCustomCameraFOV)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			camFov -= 2.5f * delta;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			camFov += 2.5f * delta;
	}


	if (m_bFreeCam)
	{
		XMMATRIX rotMat = XMMatrixRotationRollPitchYaw(camRot.X, camRot.Y, camRot.Z);

		XMVECTOR camLookAt = XMVector3TransformCoord(defaultForward, rotMat);
		XMVECTOR camUp = XMVector3TransformCoord(defaultUp, rotMat);
		XMVECTOR camRight = XMVector3TransformCoord(defaultRight, rotMat);
		XMVector3Normalize(camLookAt);
		XMVector3Normalize(camUp);
		XMVector3Normalize(camRight);
		XMFLOAT3 cL, cU, cR;
		XMStoreFloat3(&cL, camLookAt);
		XMStoreFloat3(&cU, camUp);
		XMStoreFloat3(&cR, camRight);

		camMat.forward = { cL.x, cL.y, cL.z };
		camMat.up = { cU.x, cU.y, cU.z };
		camMat.right = { cR.x, cR.y, cR.z };
	}
	if (m_bFreeCam)
	{
		cam->mat.pos =  cam->mat2.pos = camMat.pos;
		cam->mat.right = cam->mat2.right = camMat.right;
		cam->mat.forward = cam->mat2.forward = camMat.forward;
		cam->mat.up = cam->mat2.up = camMat.up;

	}
	else
	{
		camMat.pos = cam->mat.pos;
	}

	if (TheCamera)
	{
		if (m_bCustomCameraFOV)
			TheCamera->mFOV = camFov;
		else
			camFov = TheCamera->mFOV;
	}
}

void UMVC3Menu::DrawCameraTab()
{
	UMVC3MainCamera* cam = GetMainCamera();

	if (!cam)
		return;
#ifdef _DEBUG
	ImGui::Text("%p", cam);


	ImGui::InputFloat4("Pr", &cam->mat.M[0][0]);
	ImGui::InputFloat4("Pu", &cam->mat.M[1][0]);
	ImGui::InputFloat4("Pf", &cam->mat.M[2][0]);
	ImGui::InputFloat4("Pp", &cam->mat.M[3][0]);
	ImGui::Separator();
	ImGui::Separator();
	ImGui::InputFloat4("Sr", &cam->mat2.M[0][0]);
	ImGui::InputFloat4("Su", &cam->mat2.M[1][0]);
	ImGui::InputFloat4("Sf", &cam->mat2.M[2][0]);
	ImGui::InputFloat4("Sp", &cam->mat2.M[3][0]);


	ImGui::Separator();
#endif

	ImGui::InputFloat3("X | Y | Z", &camMat.pos.X);
	ImGui::InputFloat3("Pitch | Yaw | Roll", &camRot.X);


	ImGui::Separator();
	ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);
	ImGui::SameLine();
	ShowHelpMarker("FOV won't update while free camera is active!");
	ImGui::InputFloat("FOV", &camFov);


	ImGui::Separator();
	ImGui::Checkbox("Enable Free Camera", &m_bFreeCam);
	ImGui::SameLine(); ShowHelpMarker("Allows to move camera with keyboard. Keys can be changed in the Settings menu or in the .ini file. Hotkey can be assigned in Settings menu.");

	if (m_bFreeCam)
	{
		ImGui::InputFloat("Free Camera Speed", &m_fFreeCameraSpeed);
		ImGui::InputFloat("Free Camera Rotation Speed", &m_fFreeCameraRotationSpeed);

	}

}

void UMVC3Menu::DrawMiscTab()
{
	ImGui::Checkbox("Disable Game HUD", &m_bDisableHUD);
	ImGui::SameLine();
	ShowHelpMarker(eKeyboardMan::KeyToString(SettingsMgr->iToggleHUDKey));
	ImGui::Checkbox("Disable All HUD", &m_bDisableHUDTotal);
	ImGui::Checkbox("Disable Effects", &m_bDisableEffects);
}

void UMVC3Menu::DrawSettings()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 35 * ImGui::GetFontSize(), 35 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SM_Settings]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI",
		"Keys",
	};

	enum eSettings {
		MENU,
		INI,
		KEYS,
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to umvc3hook_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat("##", &SettingsMgr->fMenuScale);
		ImGui::PopItemWidth();
		break;
	case INI:
		ImGui::TextWrapped("These settings control UMVC3Hook.ini options. Any changes require game restart to take effect.");
		ImGui::Checkbox("Debug Console", &SettingsMgr->bEnableConsoleWindow);
		break;
	case KEYS:
		if (m_bPressingKey)
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");

		if (ImGui::Button("Reset Keys", { -FLT_MIN, 0 }))
		{
			SettingsMgr->ResetKeys();
			Notifications->SetNotificationTime(5500);
			Notifications->PushNotification("Keys reset! Remember to save.");

		}
		ImGui::Separator();
		ImGui::LabelText("##", "Core");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iHookMenuOpenKey, "Open/Close Menu", "menu");
		ImGui::Separator();
		ImGui::LabelText("##", "Camera");
		ImGui::Separator();

		KeyBind(&SettingsMgr->iFreeCameraKeyFOVPlus, "FOV+", "fov_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyFOVMinus, "FOV-", "fov_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyYawPlus, "Yaw+", "ya_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYawMinus, "Yaw-", "ya_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchPlus, "Pitch+", "pi_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchMinus, "Pitch-", "pi_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollPlus, "Roll+", "r_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollMinus, "Roll-", "r_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyXPlus, "X+", "x_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyXMinus, "X-", "x_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYPlus, "Y+", "y_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYMinus, "Y-", "y_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyZPlus, "Z+", "z_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyZMinus, "Z-", "z_minus");


		ImGui::Separator();
		ImGui::LabelText("##", "Misc");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iToggleFreeCameraKey, "Toggle Free Camera", "fcam");
		KeyBind(&SettingsMgr->iToggleHUDKey, "Toggle HUD", "thud");
		ImGui::Separator();

		if (m_bPressingKey)
		{
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				*m_pCurrentVarToChange = result;
				m_bPressingKey = false;
			}

		}
		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(5500);
		Notifications->PushNotification("Settings saved to UMVC3Hook.ini and umvc3hook_user.ini!");
		GUIImplementationDX9::RequestFontReload();
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

void UMVC3Menu::DrawKeyBind(char* name, int* var)
{
	ImGui::SameLine();

	static char butName[256] = {};
	sprintf(butName, "%s##key%s", eKeyboardMan::KeyToString(*var), name);
	if (ImGui::Button(butName))
	{
		m_bPressingKey = true;
		m_pCurrentVarToChange = var;
	}
}

void UMVC3Menu::KeyBind(int* var, char* bindName, char* name)
{
	ImGui::LabelText("##", bindName);
	DrawKeyBind(name, var);
}
