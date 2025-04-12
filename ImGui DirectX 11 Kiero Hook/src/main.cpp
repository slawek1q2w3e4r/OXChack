#include "includes.h"
#include <filesystem>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
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

void Render()
{
    // ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (MenuConfig::ShowMenu)
    {
        
        if (ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
            ImGui::BeginTabBar("Cheat");
            if (ImGui::BeginTabItem("ESP"))
            {
				Gui.MyCheckBox2("Master ESP", &MenuConfig::MasterESP);
         
				ImGui::Separator();
                ImGui::Text("ESP Settings");
                ImGui::Separator();

				if (MenuConfig::MasterESP)
				{
                    Gui.MyCheckBox3("Enable ESP", &MenuConfig::ShowBoxESP);
                    ImGui::SameLine();
                    ImGui::ColorEdit4("BoxColor", reinterpret_cast<float*>(&MenuConfig::BoxColor), ImGuiColorEditFlags_NoInputs);

                    Gui.MyCheckBox3("Healt Bar", &MenuConfig::ShowHealthBar);

					Gui.MyCheckBox3("Enable Glow", &MenuConfig::ShowGlow);
					ImGui::SameLine();
					ImGui::ColorEdit4("GlowColor", reinterpret_cast<float*>(&MenuConfig::GlowColor), ImGuiColorEditFlags_NoInputs);
				}

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Visuals"))
            {
				ImGui::Separator();
				ImGui::Text("World");
                ImGui::Separator();

				Gui.MyCheckBox3("Night Mode", &MenuConfig::NightMode);
				Gui.MyCheckBox3("Enable Crosshair", &MenuConfig::ShowCrosshair);
				Gui.MyCheckBox3("No Flash", &MenuConfig::NoFlash);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("RageBot"))
            {
				Gui.MyCheckBox2("Master Switch", &MenuConfig::MasterRageBot);
                ImGui::Separator();
				ImGui::Text("RageBot Settings");
                ImGui::Separator();

                if (MenuConfig::MasterRageBot)
                {
                    ImGui::Combo("AntiAim Type", &MenuConfig::antiAimType, "No AntiAim\0Spinbot\0Backward\0");
                }	
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Misc"))
            {
				ImGui::Separator();
				ImGui::Text("Misc Settings");
				ImGui::Separator();

				Gui.MyCheckBox3("OBS Bypass", &MenuConfig::OBSBypass);

                ImGui::EndTabItem();
            }

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
                    ResetToDefault();
                }

                ImGui::EndTabItem();
                
            }
            ImGui::EndTabBar();

        }
        ImGui::End();
    }

    if (MenuConfig::ShowBoxESP && MenuConfig::MasterESP)
    {
        V::ESP::PlayerESP();
    }

    if (MenuConfig::ShowCrosshair && MenuConfig::MasterESP)
    {
        V::Crosshair();
    }

    if (MenuConfig::ShowGlow && MenuConfig::MasterESP)
    {
        V::ESP::Glow();
    }

    if (MenuConfig::NoFlash)
    {
        V::NoFlash();
    }

    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    if (uMsg == WM_KEYDOWN && wParam == VK_INSERT)
    {
        MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;
        }
        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }
    
    Render();
    
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    Console::CreateConsole();

    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
        }
    } while (!init_hook);

    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);

        CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);

        break;
    case DLL_PROCESS_DETACH:
        kiero::shutdown();
        break;
    }
    return TRUE;
}