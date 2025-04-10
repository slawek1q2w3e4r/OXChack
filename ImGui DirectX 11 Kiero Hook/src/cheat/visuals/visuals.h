#pragma once
#include "../../math/math.h"
#include <cstddef>
#include <cstdint>
#include "../../../src/includes.h"

namespace O
{
	constexpr std::ptrdiff_t dwEntityList = 0x1A1F730;
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1874050;
	constexpr std::ptrdiff_t dwViewMatrix = 0x1A89130;
	constexpr std::ptrdiff_t dwViewAngles = 0x1A933C0;
	constexpr std::ptrdiff_t dwGlowManager = 0x1A84190;
	constexpr std::ptrdiff_t dwLocalPlayerController = 0x1A6E9C0;

	constexpr std::ptrdiff_t m_hPlayerPawn = 0x814;

	constexpr std::ptrdiff_t m_iHealth = 0x344;
	constexpr std::ptrdiff_t m_iTeamNum = 0x3E3;
	constexpr std::ptrdiff_t m_iFlags = 0x2F1;

	constexpr std::ptrdiff_t m_vOldOrigin = 0x1324;

	constexpr std::ptrdiff_t m_flFlashDuration = 0x140C;

	constexpr std::ptrdiff_t m_glowEntity = 0xD28;
	constexpr std::ptrdiff_t m_GlowOverlay = 0xD48;

	constexpr std::ptrdiff_t attack = 0x186C850;
	constexpr std::ptrdiff_t attack2 = 0x186C8E0;
	constexpr std::ptrdiff_t back = 0x186CB20;
	constexpr std::ptrdiff_t duck = 0x186CDF0;
	constexpr std::ptrdiff_t forward = 0x186CA90;
	constexpr std::ptrdiff_t jump = 0x186CD60;
	constexpr std::ptrdiff_t left = 0x186CBB0;
	constexpr std::ptrdiff_t lookatweapon = 0x1A92F10;
	constexpr std::ptrdiff_t reload = 0x186C7C0;
	constexpr std::ptrdiff_t right = 0x186CC40;
	constexpr std::ptrdiff_t showscores = 0x1A92DF0;
	constexpr std::ptrdiff_t sprint = 0x186C730;
	constexpr std::ptrdiff_t turnleft = 0x186C970;
	constexpr std::ptrdiff_t turnright = 0x186CA00;
	constexpr std::ptrdiff_t use = 0x186CCD0;
	constexpr std::ptrdiff_t zoom = 0x1A92E80;
}

namespace V
{
	extern uintptr_t client;
	namespace ESP
	{
		extern void PlayerESP();
		extern void Glow();	
	}

	namespace Flags
	{
		extern void flags();
	}

	extern void Crosshair();
	extern void NightMode();
	extern void NoFlash();
}

namespace Console
{
	extern void CreateConsole();
}
