#include "visuals.h"
#include "../../../src/includes.h"

uintptr_t V::client = (uintptr_t)GetModuleHandle("client.dll");

void V::ESP::PlayerESP()
{
    float(*ViewMatrix)[4][4] = (float(*)[4][4])(client + O::dwViewMatrix);

    auto localPawn = *(uintptr_t*)(client + O::dwLocalPlayerPawn);
    if (!localPawn)
        return;

    auto localTeam = *(int*)(localPawn + O::m_iTeamNum);

    auto entityList = *(uintptr_t*)(client + O::dwEntityList);
    if (!entityList)
        return;

    if (!MenuConfig::ShowBoxESP)
        return;

    ImColor boxColor = MenuConfig::BoxColor;

    for (int i = 1; i < 64; i++)
    {
        uintptr_t list_entry1 = *(uintptr_t*)(entityList + (8 * ((i & 0x7FFF) >> 9)) + 16);
        if (!list_entry1)
            continue;

        uintptr_t playerController = *(uintptr_t*)(list_entry1 + 120 * (i & 0x1FF));
        if (!playerController)
            continue;

        uint32_t playerPawn = *(uint32_t*)(playerController + O::m_hPlayerPawn);
        if (!playerPawn)
            continue;

        uintptr_t list_entry2 = *(uintptr_t*)(entityList + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
        if (!list_entry2)
            continue;

        uintptr_t pCSPlayerPawnPtr = *(uintptr_t*)(list_entry2 + 120 * (playerPawn & 0x1FF));
        if (!pCSPlayerPawnPtr)
            continue;

        int health = *(int*)(pCSPlayerPawnPtr + O::m_iHealth);
        if (health <= 0)
            continue;

        int team = *(int*)(pCSPlayerPawnPtr + O::m_iTeamNum);
        if (team == localTeam)
            continue;

        Vector3 feetpos = *(Vector3*)(pCSPlayerPawnPtr + O::m_vOldOrigin);
        Vector3 headpos = { feetpos.x, feetpos.y, feetpos.z + 65.0f };

        Vector2 feet, head;

        if (feetpos.WordlToScreen(feet, ViewMatrix) && headpos.WordlToScreen(head, ViewMatrix))
        {
            int flags = *(int*)(pCSPlayerPawnPtr + O::m_iFlags);
            bool isCrouching = (flags & (1 << 0)) != 0;

            float height = (feet.y - head.y) * (isCrouching ? 0.7f : 1.09f);
            float width = height * 0.6f;
            float x = feet.x - width / 2;

            // Rysowanie boxa
            ImGui::GetBackgroundDrawList()->AddRect(
                { x, head.y },
                { x + width, head.y + height },
                boxColor
            );

            // HEALTH BAR
            float healthPerc = std::clamp(health / 100.0f, 0.0f, 1.0f);
            float barHeight = height * healthPerc;
            float barWidth = 4.0f;
            float barX = x - barWidth - 2.0f;
            float barY = head.y + (height - barHeight);

            ImColor healthColor = ImColor::HSV(healthPerc * 0.33f, 1.0f, 1.0f); // zielony do czerwonego

            // Tło paska zdrowia
            ImGui::GetBackgroundDrawList()->AddRectFilled(
                { barX, head.y },
                { barX + barWidth, head.y + height },
                IM_COL32(0, 0, 0, 150)
            );

            // Pasek zdrowia
            ImGui::GetBackgroundDrawList()->AddRectFilled(
                { barX, barY },
                { barX + barWidth, head.y + height },
                healthColor
            );
        }

    }
}

void V::ESP::Glow()
{
    
}

void V::Crosshair()
{
	if (MenuConfig::ShowCrosshair)
	{
		// Rysowanie celownika
		ImGui::GetBackgroundDrawList()->AddLine(
			{ (float)(GetSystemMetrics(SM_CXSCREEN) / 2), (float)(GetSystemMetrics(SM_CYSCREEN) / 2 - 10) },
			{ (float)(GetSystemMetrics(SM_CXSCREEN) / 2), (float)(GetSystemMetrics(SM_CYSCREEN) / 2 + 10) },
			ImColor(255, 0, 0, 255), 1.5f
		);
		ImGui::GetBackgroundDrawList()->AddLine(
			{ (float)(GetSystemMetrics(SM_CXSCREEN) / 2 - 10), (float)(GetSystemMetrics(SM_CYSCREEN) / 2) },
			{ (float)(GetSystemMetrics(SM_CXSCREEN) / 2 + 10), (float)(GetSystemMetrics(SM_CYSCREEN) / 2) },
			ImColor(255, 0, 0, 255), 1.5f
		);
	}
}

void V::NightMode()
{
	
}

inline void V::NoFlash()
{ 

}

void Console::CreateConsole()
{
    if (AllocConsole())
    {

        SetConsoleTitle("Visit OXChack.ddns.net for updates!!");

        FILE* pConsole;
        freopen_s(&pConsole, "CONOUT$", "w", stdout);
        freopen_s(&pConsole, "CONOUT$", "w", stderr);
        freopen_s(&pConsole, "CONIN$", "r", stdin);
        std::cout << "Console successfully created!" << std::endl;
		std::cout << "Join dc: https://discord.gg/RDB7QZrpkj for updates" << std::endl;
    }
    else
    {
        std::cerr << "Failed to allocate console. Error: " << GetLastError() << std::endl;
    }
}


