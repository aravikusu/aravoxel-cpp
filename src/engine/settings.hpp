#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include "engine.hpp"
#include "../util/toml.hpp"

class Settings
{
public:
    Settings();
    ~Settings();
    
    int getWidth();
    int getHeight();

private:
    void setDefault();
    void setExisting();
    void save(bool showMessage = true);

    int windowWidth = 1920;
    int windowHeight = 1080;
    int chunkSize = 32;

    bool foundButBroken = false;
    toml::table settings;
};