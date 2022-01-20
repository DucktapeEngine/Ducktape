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

#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/debug.h>
#include <SFML/Audio.hpp>
#include <vector>

namespace DT
{
	class AudioSource : public BehaviourScript
	{
	private:
		bool isMusic = false;
		std::string path;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		sf::Music music;

	public:
		AudioSource(Entity *_entity);

		void load(std::string _path, bool _isMusic);

		void pause();
		void play();
		void stop();

		void setSeek(float sec);
		float getSeek();

		void setLoop(bool loop);
		bool getLoop();

		void setPitch(float pitch);
		float getPitch();

		void setVolume(float volume);
		float getVolume();

		void setDistance(float distance);
		float getDistance();

		void setSpatial(bool spatial);
		bool getSpatial();

		void onApplicationClose();
	};
}

#endif