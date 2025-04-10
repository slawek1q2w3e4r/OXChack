#pragma once
#define UNICODE
#define _UNICODE
#ifndef IMGUI_IMPL
#define IMGUI_IMPL
#endif
#include <Windows.h>
#include <d3d11.h>
#include <TlHelp32.h>
#include <iostream>
#include <dxgi.h>
#include <vector>
#include <mutex>
#include <tlhelp32.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include "../ext/kiero/kiero.h"
#include "../ext/OS-ImGui/imgui/imgui.h"
#include "../ext/OS-ImGui/imgui/imgui_impl_win32.h"
#include "../ext/OS-ImGui/imgui/imgui_impl_dx11.h"
#include "../ext/OS-ImGui/OS-ImGui.h"
#include "../src/cheat/visuals/visuals.h"
#include "../src/utils/ConfigMenu.hpp"
#include "../src/math/math.h"
#include <windows.h>
#include "../src/utils/input.h" 
#define TICK_RATE 64

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef uintptr_t PTR;
