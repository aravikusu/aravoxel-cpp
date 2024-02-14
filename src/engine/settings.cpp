#include "settings.hpp"

int Settings::getWidth() const {
    return windowWidth;
}

int Settings::getHeight() const {
    return windowHeight;
}

void Settings::setDefault() {
    settings = toml::table{
        {"name", engine::ENGINE_NAME},
        {"version", engine::ENGINE_VERSION},
        {
            "window", toml::table{
                {"width", 1920},
                {"height", 1080}
            }
        },
        {"voxel_settings", toml::table{{"chunk_size", 32}}}
    };

    if (!foundButBroken)
        save(false);

    std::cout << engine::console::success() << "Default settings.toml has been created.\n";
}

void Settings::setExisting() {
    const std::optional<int> width = settings["window"]["width"].value<int>();
    const std::optional<int> height = settings["window"]["height"].value<int>();
    const std::optional<int> cnkSize = settings["voxel_settings"]["chunk_size"].value<int>();

    if (width)
        windowWidth = width.value();
    if (height)
        windowHeight = height.value();
    if (cnkSize)
        chunkSize = cnkSize.value();
}

void Settings::save(const bool showMessage) const {
    std::ofstream file("settings.toml");
    file << settings;
    file.close();

    if (showMessage)
        std::cout << engine::console::success() << "Settings have been saved successfully.\n";
}

Settings::Settings() {
    if (std::filesystem::exists(engine::SETTINGS_FILE)) {
        std::cout << engine::console::info() << "settings.toml was found.\n";
        try {
            settings = toml::parse_file(engine::SETTINGS_FILE);
            setExisting();
            std::cout << engine::console::success() << "settings.toml was successfully read.\n";
        } catch (const toml::parse_error &err) {
            foundButBroken = true;
            std::cout << engine::console::error() << "settings.toml could not be read: " << err << "\n";
            std::cout << engine::console::warning() <<
                    "Resorting to default settings. Any changes you make to your settings this session will not be saved.\n";
            setDefault();
        }
    } else {
        std::cout << engine::console::info() << "settings.toml was not found. Creating default settings file.\n";
        setDefault();
    }
}

Settings::~Settings() {
    if (foundButBroken) {
        std::cout << engine::console::warning() <<
                "Settings were not saved as we are using defaults due to a broken settings.toml.\n";
    }
}
