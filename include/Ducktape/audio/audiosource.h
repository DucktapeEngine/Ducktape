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
	/**
	 * @brief Component for playing Audio.
	 * 
	 * Attaching this component to an entity lets you play audio. Use the
	 * AudioSource::loadSound() / AudioSource::loadMusic() methods to load sound/music
	 * from a specified path, and the AudioSource::play(), AudioSource::stop(),
	 * AudioSource::pause() functions to control the playback of the audio.
	 * Ducktape supports the .wav, .ogg, .flac audio formats. Due to licensing issues, .mp3 is
	 * not supported as of now. 
	 * 
	 * Usage can be found in the Manual: https://ducktapeengine.github.io/manual/audio.html
	 */
	class AudioSource : public BehaviourScript
	{
	private:
		bool isMusic = false;
		std::string path;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		sf::Music music;

	public:
		/**
		 * @brief Play a sound from a specified path.
		 * 
		 * Use this method to load and play a sound from a specified path. It should be used for
		 * small sounds that can fit in memory and should suffer no lag when they are 
		 * played. Examples are gun shots, foot steps, etc.
		 * 
		 * @param loadPath Path to the audio file to load.
		 */
		void loadSound(std::string loadPath);

		/**
		 * @brief Play a music from a specified path.
		 * 
		 * Use this method to load and play a music from a specified path. Unlike AudioSource::loadSound()
		 * It doesn't load all the audio data into memory, instead it streams it on the fly from the
		 * source file. It is typically used to play compressed music that lasts several minutes, and
		 * would otherwise take many seconds to load and eat hundreds of MB in memory.
		 * 
		 * @param loadPath Path to the audio file to load.
		 */
		void loadMusic(std::string loadPath);

		/**
		 * @brief Pause the currently playing sound.
		 */
		void pause();

		/**
		 * @brief Continue playing the currently paused sound.
		 */
		void play();

		/**
		 * @brief Stop the currently playing sound.
		 */
		void stop();

		/**
		 * @brief Set the seek to/Move to a specific time (denoted in seconds).
		 * 
		 * @param seconds The number of seconds to seek to.
		 */
		void setSeek(float seconds);

		/**
		 * @brief Get the time the seek/player is currently on (denoted in seconds).
		 * 
		 * @return `float` The time the seek/player is currently on (denoted in seconds).
		 */
		float getSeek();

		/**
		 * @brief Set if the sound must loop or not once it ends.
		 * 
		 * @param loop If the sound must loop or not once it ends.
		 */
		void setLoop(bool loop);

		/**
		 * @brief Get if the sound is set to loop or not once it ends.
		 * 
		 * @return `bool` If the sound is set to loop or not once it ends.
		 */
		bool getLoop();

		/**
		 * @brief Set the pitch of the sound.
		 * 
		 * @param pitch The pitch of the sound.
		 */
		void setPitch(float pitch);

		/**
		 * @brief Get the pitch of the sound.
		 * 
		 * @return `float` The pitch of the sound.
		 */
		float getPitch();

		/**
		 * @brief Set the volume of the sound.
		 * 
		 * @param volume The volume of the sound.
		 */
		void setVolume(float volume);

		/**
		 * @brief Get the volume of the sound.
		 * 
		 * @return `float` The volume of the sound.
		 */
		float getVolume();

		/**
		 * @brief Set the distance the sound must be played from, if spatial audio
		 * is enabled using AudioSource::setSpatial(true).
		 * 
		 * @param distance The distance the sound must be played from.
		 */
		void setDistance(float distance);

		/**
		 * @brief Get the distance the sound must be played from, if spatial audio
		 * is enabled using AudioSource::setSpatial(true).
		 * 
		 * @return `float` The distance the sound must be played from. 
		 */
		float getDistance();

		/**
		 * @brief Set if the sound is spatial or not.
		 * 
		 * @param spatial If the sound is spatial or not.
		 */
		void setSpatial(bool spatial);

		/**
		 * @brief Get if the sound is spatial or not.
		 * 
		 * @return `bool` If the sound is spatial or not.
		 */
		bool getSpatial();

		/**
		 * @cond section label="inherited from BehaviourScript"
		 */
		void onApplicationClose();
		/**
		 * @endcond
		 */
	};
}

#endif