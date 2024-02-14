#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include "engine.hpp"
#include "../util/toml.hpp"

class Settings {
public:
    Settings();

    ~Settings();

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

private:
    void setDefault();

    void setExisting();

    void save(bool showMessage) const;

    int windowWidth = 1920;
    int windowHeight = 1080;
    int chunkSize = 32;

    bool foundButBroken = false;
    toml::table settings;
};
