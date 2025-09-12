#include "Utils/TextureManager.hpp"
#include <SFML/Graphics.hpp>
#include <string>   
#include "Utils/logging.hpp"

sf::Texture& TextureManager::getTexture(const std::string& name){
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile("assets/textures/" + name + ".png")) {
        logging::ERROR("Failed to load texture: " + name);
        throw std::runtime_error("Failed to load texture: " + name);
    }
    textures[name] = std::move(texture);

    textures[name].setSmooth(false); // pixel art, no smoothing
    textures[name].setRepeated(false); // no repeating by default

    return textures[name];
}