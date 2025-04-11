#include "ConfigMenu.hpp"
#include "ConfigSaver.hpp"
#include <filesystem>

namespace MenuConfig {

    void RenderConfigMenu() {
		// Config
		if (ImGui::BeginTabItem("Config "))
		{
			static char configNameBuffer[128] = "";

			ImGui::InputText("New Config Name", configNameBuffer, sizeof(configNameBuffer));

			if (ImGui::Button("Create Config"))
			{
				std::string configFileName = std::string(configNameBuffer) + ".config";
				MyConfigSaver::SaveConfig(configFileName);
			}

			ImGui::Separator();

			static int selectedConfig = -1;

			const std::string configDir = MenuConfig::path;
			static std::vector<std::string> configFiles;

			configFiles.clear();
			for (const auto& entry : std::filesystem::directory_iterator(configDir))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".config")
				{
					configFiles.push_back(entry.path().filename().string());
				}
			}

			for (int i = 0; i < configFiles.size(); ++i)
			{
				if (ImGui::Selectable(configFiles[i].c_str(), selectedConfig == i))
				{
					selectedConfig = i;
				}
			}

			if (selectedConfig != -1)
			{
				ImGui::Text("Selected Config: %s", configFiles[selectedConfig].c_str());
			}

			if (ImGui::Button("Load Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::LoadConfig(selectedConfigFile);
			}

			if (ImGui::Button("Save Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::SaveConfig(selectedConfigFile);
			}

			ImGui::Separator();

			if (ImGui::Button("Delete Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				std::string fullPath = configDir + "/" + selectedConfigFile;
				if (std::remove(fullPath.c_str()) == 0)
				{
					configFiles.erase(configFiles.begin() + selectedConfig);
					selectedConfig = -1;
				}
				else
				{
				}
			}

			if (ImGui::Button("Reset to Default"))
			{
				MenuConfig::ResetToDefault();
			}

			ImGui::EndTabItem();
		}
    }

    void ResetToDefault() {
		MenuConfig::ShowBoxESP = false;
		MenuConfig::ShowMenu = true;
		MenuConfig::ShowCrosshair = false;
		MenuConfig::NightMode = false;
		MenuConfig::NoFlash = false;
		MenuConfig::ShowGlow = false;
		MenuConfig::MasterRageBot = false;
		MenuConfig::antiAimAngle = 0;
		MenuConfig::spinBotSpeed = 0;
		MenuConfig::NightModeIntesivity = 0;
		MenuConfig::BoxColor = ImColor(255, 255, 255, 255);
		MenuConfig::GlowColor = ImColor(255, 255, 255, 255);
		MenuConfig::OBSBypass = false;
		MenuConfig::antiAimType = 0;
		MenuConfig::MasterESP = false;
    }
}
