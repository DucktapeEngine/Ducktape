#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include "../engine/componentexecutionhandler.h"
#include <vector>
#include "../engine/scripts.h"
#include <SFML/Audio.hpp>
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

    public:
        void Load(std::string _path, bool _isMusic);

        void Pause();
        void Play();
        void Stop();

        void SetSeek(float sec);
        float GetSeek();

        void SetLoop(bool loop);
        bool GetLoop();

        void SetPitch(float pitch);
        float GetPitch();

        void SetVolume(float volume);
        float GetVolume();

        void SetDistance(float distance);
        float GetDistance();

        void SetSpatial(bool spatial);
        bool GetSpatial();

        void OnApplicationClose();
    };
}

#endif