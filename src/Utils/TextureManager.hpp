                        #pragma once

                #include <SFML/Graphics.hpp>
                      #include <string>
                  #include <unordered_map>
                      #include <memory>
                      #include <mutex>

                   class TextureManager {
                           public:
              // Delete copy and move semantics
       TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
         TextureManager(TextureManager&&) = delete;
    TextureManager& operator=(TextureManager&&) = delete;

                // Access the single instance
           static TextureManager& getInstance() {
        static TextureManager instance{}; // Thread-safe since C++11
                      return instance;
                              }

      sf::Texture& getTexture(const std::string& name);

                          private:
    std::unordered_map<std::string, sf::Texture> textures;

                         protected:
                 TextureManager() = default;
                ~TextureManager() = default;
                             };