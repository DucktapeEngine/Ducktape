#include "audiosource.h"
using namespace DT;

void AudioSource::Load(std::string _path, bool _isMusic)
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

void AudioSource::Pause()
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

void AudioSource::Play()
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

void AudioSource::Stop()
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

void AudioSource::SetSeek(float sec)
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

float AudioSource::GetSeek()
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

AudioEffects AudioSource::GetAudioEffects()
{
    return audioEffects;
}

void AudioSource::SetAudioEffects(AudioEffects _audioEffects)
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