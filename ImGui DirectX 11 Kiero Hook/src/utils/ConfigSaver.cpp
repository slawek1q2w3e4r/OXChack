#include "ConfigSaver.hpp"
#include "../../src/includes.h"

void MyConfigSaver::SaveConfig(const std::string& filename)
{
	std::ofstream configFile(MenuConfig::path + '/' + filename);
	if (configFile.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
	}

	configFile << "ShowBoxESP=" << MenuConfig::ShowBoxESP << "\n";
	configFile << "ShowMenu=" << MenuConfig::ShowMenu << "\n";
	configFile << "ShowCrosshair=" << MenuConfig::ShowCrosshair << "\n";
	configFile << "NightMode=" << MenuConfig::NightMode << "\n";
	configFile << "NoFlash=" << MenuConfig::NoFlash << "\n";
	configFile << "ShowGlow=" << MenuConfig::ShowGlow << "\n";
	configFile << "MasterRageBot=" << MenuConfig::MasterRageBot << "\n";
	configFile << "MasterESP=" << MenuConfig::MasterESP << "\n";
	configFile << "antiAimType=" << MenuConfig::antiAimType << "\n";
	configFile << "antiAimAngle=" << MenuConfig::antiAimAngle << "\n";
	configFile << "spinBotSpeed=" << MenuConfig::spinBotSpeed << "\n";
	configFile << "NightModeIntesivity=" << MenuConfig::NightModeIntesivity << "\n";
	configFile << "BoxColor=" << MenuConfig::BoxColor << "\n";
	configFile << "GlowColor=" << MenuConfig::GlowColor << "\n";
	configFile << "OBSBypass=" << MenuConfig::OBSBypass << "\n";
	configFile.close();
}

void MyConfigSaver::LoadConfig(const std::string& filename)
{
	std::ifstream configFile(MenuConfig::path + '/' + filename);
	if (!configFile.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(configFile, line))
	{
		std::istringstream iss(line);
		std::string key;
		if (iss >> key)
		{
			if (key == "ShowBoxESP=") iss >> MenuConfig::ShowBoxESP;
			else if (key == "ShowMenu=") iss >> MenuConfig::ShowMenu;
			else if (key == "ShowCrosshair=") iss >> MenuConfig::ShowCrosshair;
			else if (key == "NightMode=") iss >> MenuConfig::NightMode;
			else if (key == "NoFlash=") iss >> MenuConfig::NoFlash;
			else if (key == "ShowGlow=") iss >> MenuConfig::ShowGlow;
			else if (key == "MasterRageBot=") iss >> MenuConfig::MasterRageBot;
			else if (key == "MasterESP=") iss >> MenuConfig::MasterESP;
			else if (key == "antiAimType=")
			{
				int value;
				if (iss >> value)
					MenuConfig::antiAimType = value;
			}
			else if (key == "antiAimAngle=")
			{
				int value;
				if (iss >> value)
					MenuConfig::antiAimAngle = value;
			}
			else if (key == "spinBotSpeed=")
			{
				int value;
				if (iss >> value)
					MenuConfig::spinBotSpeed = value;
			}
			else if (key == "NightModeIntesivity=")
			{
				int value;
				if (iss >> value)
					MenuConfig::NightModeIntesivity = value;
			}

			else if (key == "OBSBypass=")
			{
				bool value;
				if (iss >> value)
					MenuConfig::OBSBypass = value;
			}
		}
	} 
}
