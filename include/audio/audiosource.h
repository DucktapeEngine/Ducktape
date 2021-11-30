#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

class AudioEffects
{
public:
    bool loop = false;
    float pitch = 1.0f;
    float volume = 100.0f;
    float distance = 1.0f;
    bool spatial = false;
    Vector2 position = Vector2(0.0f, 0.0f);    
};

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
    void Load(std::string _path, bool _isMusic)
    {
        path = _path;
        isMusic = _isMusic;
        if(isMusic)
        {
            if (!music.openFromFile(path))
            {
                Debug::LogError("The specified audio file: " + path + " could not be found.");
                return;
            }
            music.play();
        }
        else
        {
            if(!buffer.loadFromFile(path))
            {
                Debug::LogError("The specified audio file: " + path + " could not be found.");
                return;
            }

            sound.setBuffer(buffer);
            sound.play();
        }
    }

    void Pause()
    {
        if(isMusic)
        {
            music.pause();
        }
        else
        {
            sound.pause();
        }
    }

    void Play()
    {
        if(isMusic)
        {
            music.play();
        }
        else
        {
            sound.play();
        }
    }

    void Stop()
    {
        if(isMusic)
        {
            music.stop();
        }
        else
        {
            sound.stop();
        }
    }

    void SetSeek(float sec)
    {
        if(isMusic)
        {
            music.setPlayingOffset(sf::seconds(sec));
        }
        else
        {
            sound.setPlayingOffset(sf::seconds(sec));
        }
    }

    float GetSeek()
    {
        if(isMusic)
        {
            return music.getPlayingOffset().asSeconds();
        }
        else
        {
            return sound.getPlayingOffset().asSeconds();
        }
    }

    AudioEffects GetAudioEffects()
    {
        return audioEffects;
    }

    void SetAudioEffects(AudioEffects _audioEffects)
    {
        audioEffects = _audioEffects;
        if(isMusic)
        {
            music.setLoop(audioEffects.loop);
            music.setPitch(audioEffects.pitch);
            music.setVolume(audioEffects.volume);
            music.setMinDistance(audioEffects.distance);
            music.setRelativeToListener(audioEffects.spatial);
            music.setPosition(sf::Vector3f(audioEffects.position.x, audioEffects.position.y, 0.0f));
        }
        else
        {
            sound.setLoop(audioEffects.loop);
            sound.setPitch(audioEffects.pitch);
            sound.setVolume(audioEffects.volume);
            sound.setMinDistance(audioEffects.distance);
            sound.setRelativeToListener(audioEffects.spatial);
            sound.setPosition(sf::Vector3f(audioEffects.position.x, audioEffects.position.y, 0.0f));
        }
    }
};

#endif