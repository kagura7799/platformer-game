#include "Sounds.hpp"
#include <iostream>

void Sounds::playBackgroundMusic()
{
    if (!music.openFromFile(pathToBackgroundMusic)) {
        std::cerr << "Failed loading music: " << std::endl;
        return;
    }
    
    music.setLoop(true);
    music.play();
}