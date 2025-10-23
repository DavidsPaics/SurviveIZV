#pragma once
#include <Entities/Entity.hpp>

class InfectedSpageti : public Entity{
public:
    InfectedSpageti(World& worldRef);
    void update(float deltaTime) override;
};