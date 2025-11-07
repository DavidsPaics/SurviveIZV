#include "Level.hpp"
#include "Core/World.hpp"
#include "Entities/Entity.hpp"

Level::Level(World& world, Player& player, std::vector<std::unique_ptr<Entity>>& entities): world(world), player(player), entities(entities){}

void Level::update(float dt){};
void Level::playerEnter(std::string lastLevelName = ""){};
void Level::playerExit(){};