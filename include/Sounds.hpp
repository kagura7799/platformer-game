#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <SFML/Audio.hpp>

class Sounds
{
private:
    sf::Music music;
    std::string pathToBackgroundMusic = "/home/kagura/cpp/platformer-game/music/battle.ogg";

public:
    void playBackgroundMusic();
};

#endif