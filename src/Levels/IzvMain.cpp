#include "IzvMain.hpp"
#include "Core/World.hpp"
#include "Entities/Player.hpp"
#include <memory>

IzvMain::IzvMain(World& world, Player& player, std::vector<std::unique_ptr<Entity>>& entities) : Level(world, player, entities){

}