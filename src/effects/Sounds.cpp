#include "Sounds.hpp"
#include <iostream>

void Sounds::loadSound(const std::string& name, const std::string& filePath, bool loop) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Failed to load sound: " << filePath << std::endl;
        return;
    }

    soundBuffers[name] = buffer; 
    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    sound.setLoop(loop); 
    sounds[name] = sound;
}

void Sounds::playSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.play();
    }
}

void Sounds::stopSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.stop();
    }
}

void Sounds::playSoundIfNotPlaying(const std::string& soundName) {
    if (!isSoundPlaying(soundName)) {
        playSound(soundName);
    }
}

bool Sounds::isSoundPlaying(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        return it->second.getStatus() == sf::Sound::Playing;
    }
    return false;
}
