             #pragma once
    #include <Entities/Entity.hpp>

 class InfectedKvass : public Entity{
                public:
    InfectedKvass(World& worldRef);
    void update(float deltaTime) override;
                  };