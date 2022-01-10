/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Ducktape/audio/audiosource.h>
using namespace DT;

AudioSource::AudioSource(Entity* _entity)
{
    entity = _entity;
}

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

void AudioSource::SetLoop(bool loop)
{
    if(isMusic)
    {
        music.setLoop(loop);
    }
    else
    {
        sound.setLoop(loop);
    }
}

bool AudioSource::GetLoop()
{
    if(isMusic)
    {
        return music.getLoop();
    }
    else
    {
        return sound.getLoop();
    }
}

void AudioSource::SetPitch(float pitch)
{
    if(isMusic)
    {
        music.setPitch(pitch);
    }
    else
    {
        sound.setPitch(pitch);
    }
}

float AudioSource::GetPitch()
{
    if(isMusic)
    {
        return music.getPitch();
    }
    else
    {
        return sound.getPitch();
    }
}

void AudioSource::SetVolume(float volume)
{
    if(isMusic)
    {
        music.setVolume(volume);
    }
    else
    {
        sound.setVolume(volume);
    }
}

float AudioSource::GetVolume()
{
    if(isMusic)
    {
        return music.getVolume();
    }
    else
    {
        return sound.getVolume();
    }
}

void AudioSource::SetDistance(float distance)
{
    if(isMusic)
    {
        music.setMinDistance(distance);
    }
    else
    {
        sound.setMinDistance(distance);
    }
}

float AudioSource::GetDistance()
{
    if(isMusic)
    {
        return music.getMinDistance();
    }
    else
    {
        return sound.getMinDistance();
    }
}

void AudioSource::SetSpatial(bool spatial)
{
    if(isMusic)
    {
        music.setRelativeToListener(spatial);
    }
    else
    {
        sound.setRelativeToListener(spatial);
    }
}

bool AudioSource::GetSpatial()
{
    if(isMusic)
    {
        return music.isRelativeToListener();
    }
    else
    {
        return sound.isRelativeToListener();
    }
}

void AudioSource::OnApplicationClose()
{
    Stop();
}