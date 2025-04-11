#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace MyConfigSaver {
    extern void SaveConfig(const std::string& filename);
    extern void LoadConfig(const std::string& filename);
}