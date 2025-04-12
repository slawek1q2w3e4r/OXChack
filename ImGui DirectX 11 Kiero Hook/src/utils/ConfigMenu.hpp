#pragma once
#include "../../src/includes.h"

namespace MenuConfig
{
	inline std::string path = "";

	// --------------------BOOL--------------------

	inline bool ShowBoxESP = false;
	inline bool ShowMenu = true;
	inline bool ShowCrosshair = false;
	inline bool NightMode = false;
	inline bool NoFlash = false;
	inline bool ShowGlow = false;
	inline bool BackwordSite = false; // 0 - left   1 - right 
	inline bool ShowHealthBar = false;

	// masterswitch

	inline bool MasterRageBot = false;
	inline bool MasterESP = false;
	

	// --------------------INT--------------------

	
	inline int antiAimType = 0; //   0 - No AntiAim    1 - spinbot   2 - backword
	inline int antiAimAngle = 0; // Angle
	inline int spinBotSpeed = 0; // RPM

	inline int NightModeIntesivity = 0; // 0 - off    1 - on

	// --------------------COLOR--------------------

	inline ImColor BoxColor = ImColor(255, 255, 255, 255);
	inline ImColor GlowColor = ImColor(255, 255, 255, 255);

	// --------------------MISC--------------------

	inline bool OBSBypass = false;

}
