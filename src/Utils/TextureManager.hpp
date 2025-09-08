#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>

// Optional logging utility
#include "Utils/logging.hpp"

class TextureManager {
public:
    // Get the singleton instance
    static TextureManager& getInstance();

    sf::Texture& getTexture(const std::string& name);

    void preloadTexture(const std::string& name);

private:
    TextureManager() = default; // private constructor
    ~TextureManager() = default;

    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
};
