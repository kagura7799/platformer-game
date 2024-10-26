#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class Sounds {
public:
    void loadSound(const std::string& name, const std::string& filePath, bool loop = false);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);
    void playSoundIfNotPlaying(const std::string& soundName);
    bool isSoundPlaying(const std::string& name);

private:
    std::map<std::string, sf::Sound> sounds; 
    std::map<std::string, sf::SoundBuffer> soundBuffers;
};

#endif
