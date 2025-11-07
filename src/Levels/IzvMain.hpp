#include "Level.hpp"
#include <memory>

class IzvMain : public Level {
public:
    IzvMain(World& world, Player& player, std::vector<std::unique_ptr<Entity>>& entities);

    void update(float dt);
    void playerEnter(std::string lastIzvLevelName = "");
    void playerExit();
};