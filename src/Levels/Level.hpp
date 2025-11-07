#include <vector>
#include <string>
#include <memory>

class World; class Entity; class Player;

class Level{
public:
    Level(World& world, Player& player, std::vector<std::unique_ptr<Entity>>& entities);
    virtual void update(float dt);
    virtual void playerEnter(std::string lastLevelName = "");
    virtual void playerExit();
protected:
    World& world;
    Player& player;
    std::vector<std::unique_ptr<Entity>>& entities;
};