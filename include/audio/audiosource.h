#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include "../engine/componentexecutionhandler.h"
#include <vector>
#include "../engine/scripts.h"
#include <SFML/Audio.hpp>
#include "audioeffects.h"
#include "../engine/debug.h"

namespace DT
{
    class AudioSource : public AudioScript
    {
    private:
        bool isMusic = false;
        std::string path;
        sf::SoundBuffer buffer;
        sf::Sound sound;
        sf::Music music;

        AudioEffects audioEffects;

    public:
        void Load(std::string _path, bool _isMusic);

        void Pause();

        void Play();

        void Stop();

        void SetSeek(float sec);

        float GetSeek();

        AudioEffects GetAudioEffects();

        void SetAudioEffects(AudioEffects _audioEffects);

        void OnApplicationClose();
    };
}

#endif