#pragma once

#include <string>

namespace engine {
    inline const std::string SHADER_DIR = "src/shaders/";
    inline const std::string TEXTURE_DIR = "src/assets/textures/";
    inline const std::string SETTINGS_FILE = "settings.toml";
    inline const std::string ENGINE_NAME = "aravoxel";
    inline const std::string ENGINE_VERSION = "0.0.1";

    /// @brief Enums specifically used by the engine, such as GameState.
    namespace enums {
        enum GameState {
            INIT = 0,
            TEST = 1,
            VOXEL_WORLD = 2
        };
    }

    /// @brief Print things in a pretty manner.
    namespace console {
        inline std::string error() {
            return "[\033[0;31mERROR\033[0;37m] ";
        }

        inline std::string warning() {
            return "[\033[0;33mWARNING\033[0;37m] ";
        }

        inline std::string success() {
            return "[\033[0;32mSUCCESS\033[0;37m] ";
        }

        inline std::string info() {
            return "[\033[0;30mINFO\033[0;37m] ";
        }

        inline std::string aravoxel() {
            return "\033[0;35maravoxel\033[0;37m ";
        }
    }
}
