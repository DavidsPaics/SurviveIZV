#include "Utils/TextureManager.hpp"
#include "Utils/logging.hpp"

TextureManager& TextureManager::getInstance() {
    static TextureManager instance; // lazy initialization
    return instance;
}

sf::Texture& TextureManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return *it->second; // already loaded
    }

    // Load new texture
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile("assets/textures/" + name)) {
        logging::ERROR("Failed to load texture: " + name);
        throw std::runtime_error("Failed to load texture: " + name);
    }

    sf::Texture& ref = *texture;
    textures[name] = std::move(texture);
    logging::INFO("Loaded texture: " + name);
    return ref;
}

void TextureManager::preloadTexture(const std::string& name) {
    // Simply calls getTexture to load it
    getTexture(name);
}
