#include "..\pch.h"
#include "umvc3menu.h"
#include "..\imgui\imgui.h"
#include <iostream>
static int64 timer = GetTickCount64();

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

void UMVC3Menu::Initialize()
{
	m_bIsActive = false;
	m_bIsFocused = false;
	m_bCustomCameraFOV = false;
	m_bCustomCameraPos = false;
	m_bCustomCameraRot = false;

	m_nFreeCameraSpeed = 1;
	m_nFreeCameraRotationSpeed = 1;


	camFov = 0;
	camPos = { 0,0,0 };
	camRot = { 0,0,0 };
}

void UMVC3Menu::Process()
{
	UpdateControls();
}

void UMVC3Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetUMVC3HookVersion());
	if (ImGui::BeginTabBar("##tabs"))
	{
		
		if (ImGui::BeginTabItem("Camera Control"))
		{
			ImGui::Checkbox("Set Camera Position", &m_bCustomCameraPos);
			ImGui::InputFloat3("X | Y | Z", &camPos.X);
			ImGui::Checkbox("Set Camera Rotation", &m_bCustomCameraRot);
			ImGui::InputFloat3("rot##X | Y | Z", &camRot.X);

			ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);
			ImGui::InputFloat("FOV", &camFov);

			if (ImGui::Button("Reset FOV"))
			{
				SetCamFOV(32.0f);
				camFov = GetCamFOV();
			}


			ImGui::Separator();
			ImGui::Checkbox("Enable Freecam", &m_bFreeCam);
			ImGui::SameLine(); ShowHelpMarker("Allows to move camera with certain keys.\nRequires all toggles enabled!\nYou can configure keys in .ini file.");

			if (m_bFreeCam)
			{
				if (!m_bCustomCameraPos || !m_bCustomCameraRot || !m_bCustomCameraFOV)
					ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Check rest of the Set Camera options!");

				ImGui::InputInt("Freecam Speed", &m_nFreeCameraSpeed);
				ImGui::InputInt("Freecam Rotation Speed", &m_nFreeCameraRotationSpeed);
			}



			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	ImGui::End();
}

void UMVC3Menu::UpdateControls()
{
	if (GetAsyncKeyState(VK_F1))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		m_bIsActive ^= 1;
	}
}

bool UMVC3Menu::GetActiveState()
{
	return m_bIsActive;
}

char * GetUMVC3HookVersion()
{
	static char buffer[512] = {};
	sprintf(buffer, "UMVC3Hook by ermaccer (%s)", UMVC3HOOK_VERSION);
	return buffer;
}