#pragma once

#include <string>

namespace engine 
{
    inline const std::string SHADER_DIR = "src/shaders/";
    inline const std::string TEXTURE_DIR = "src/assets/textures/";

    inline const int SCREEN_WIDTH = 1920;
    inline const int SCREEN_HEIGHT = 1080;

    namespace console
    {
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