#pragma once
#include "Utils/math.hpp"
#include <SFML/Graphics.hpp>
#include "Utils/TextureManager.hpp"
#include <vector>

class World;

class Entity{
public:
    Entity(World& worldRef);

    virtual void update(float deltaTime);
    virtual sf::Sprite& getSprite();

    sf::Vector2f getPosition() { return position; }
    sf::Vector2f getVelocity() { return velocity; }
    void setPosition(const sf::Vector2f& pos) {position = pos;}

    void walkTo(const sf::Vector2f& pos){
        targetPos=pos;
        nextPos = pathfind(position,targetPos);
    }

protected:
    sf::Sprite sprite;
    sf::Vector2f position {0.f,0.f};
    sf::Vector2f velocity {0.f,0.f};

    World& world;

    sf::Vector2f movementDirection = {0,0};

    void resolveCollisions(const sf::Vector2f& delta);

    float terminalVelocity = 5.f;
    
    sf::Vector2f targetPos = {-1,-1};
    sf::Vector2f nextPos = {-1,-1};
    sf::Clock timeSincePathUpdate;      
    // --- Constants you can tweak ---
    float acceleration = 35.f;   // how fast it speeds up
    float drag = 7.f;              // how fast it slows down (lower = more slippery)
    float minVelocity = 0.035f;      // cutoff to stop jitter
    float maxVelocity = terminalVelocity;

private:
    //Changed by the setupAnimations function
    int selectedAnimationIndex = -1;
    int selectedOneTimeAnimationIndex=-1;
    int currentFrame = 0;
    int animationTypes = 1;
    std::vector<int> animationFrameCountPerType = {1};
    float animationFrameDelaySeconds = 0.2f;
    sf::Clock lastAnimationUpdateClock;
protected:
    /*
        animationCount - is the total amount of rows/types of animations
        animationFrames - is an initializer_list of the frame counts of each of the types
        animationFrameLengthSeconds - The seconds between each animation update (default 0.2s)
    */
    void setupAnimations(int animationCount, std::initializer_list<int> animationFrames, float animationFrameLengthSeconds=0.2f){
        assert(animationCount>0);
        assert(animationFrameLengthSeconds>0); //0 would be framerate dependant, lower is invalid
        animationTypes = animationCount;
        animationFrameCountPerType = animationFrames;
        animationFrameDelaySeconds = animationFrameLengthSeconds;
        lastAnimationUpdateClock.restart();
    }
    void playLoopingAnimation(int index){
        if (selectedAnimationIndex==index)
        return;
        assert(index>=0&&index<animationTypes);
        selectedAnimationIndex = index;
        lastAnimationUpdateClock.restart();
        currentFrame = 0;
        selectedOneTimeAnimationIndex = -1;
    }
    void playAnimationOnce(int index){
        assert(index>=0&&index<animationTypes);
        selectedOneTimeAnimationIndex = index;
        lastAnimationUpdateClock.restart();
        currentFrame = 0;
    }
    void updateAnimations(){
        if(lastAnimationUpdateClock.getElapsedTime().asSeconds()<animationFrameDelaySeconds)
        return;
        if(selectedAnimationIndex<0 && selectedOneTimeAnimationIndex<0)
        return;

        lastAnimationUpdateClock.restart();

        int textureRectX=0,textureRectY=0,animIndex=0;
        if(selectedOneTimeAnimationIndex>=0){
            animIndex = selectedOneTimeAnimationIndex;
        } else {
            animIndex = selectedAnimationIndex;
        }

        sprite.setTextureRect(sf::IntRect({currentFrame*32, animIndex*32},{32,32})); // TODO: Maybe dont hardcode sprite size, not that critical tho
        
        if(selectedOneTimeAnimationIndex>=0&&currentFrame+1>=animationFrameCountPerType.at(selectedOneTimeAnimationIndex)){
            selectedOneTimeAnimationIndex=-1;
            currentFrame = 0;
        } else {
            currentFrame+=1;
            currentFrame%=animationFrameCountPerType.at(animIndex);
        }
    }
};