#pragma once
#include "SpriteObject.h"
#include "SFML/Graphics.hpp"

class Animation :
    public SpriteObject
{

    struct Clip
    {
        std::vector<sf::Texture> textures;
        bool shouldLoop;

    };

public:
    Animation(sf::Sprite* newAnimatedSprite, std::string newBaseFilePath, float framesPerSecond, std::string newFileType = "png");
    Animation();
    void AddClip(std::string clipName, int numFrames, bool shouldLoop = false);
    void Play();
    void Play(std::string clipToPlay);
    void Stop();
    void Pause();

    void Update();

private:
    sf::Sprite* animatedSprite;
    std::string baseFilePath;
    std::string fileType;
    Clip* currentClip;
    std::map<std::string, Clip> animations;
    int currentFrame;
    sf::Time timePerFrame;
    sf::Clock aniClock;
    bool isPlaying;

};

