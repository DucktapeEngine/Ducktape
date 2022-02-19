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

#ifndef DUCKTAPE_AUDIO_AUDIOSOURCE_H_
#define DUCKTAPE_AUDIO_AUDIOSOURCE_H_

#include <vector>

#include <SFML/Audio.hpp>

#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/debug.h>

namespace DT
{
	/**
	 * @brief Component for playing Audio.
	 *
	 * Ducktape allows you to play audio in your project through the `AudioSource` component. It offers customization options like pitch, volume, loop, and spatial audio.
	 *
	 * There are two types of audio - Sound, Music. Sound is primarily for short tracks like gunshots, footsteps, or quick sound effects in general. But on the other hand, music is for long audio tracks like background soundtracks that last several minutes. The main difference behind the scene is that sounds are loaded directly into memory and played from there. Thus they are used for small sounds that fit in memory and should suffer no lag when played. Music doesn't load all the audio data into memory; instead, it streams it on the fly from the source file. It generally is used for playing compressed music that lasts several minutes, which would otherwise take many seconds to load and eat hundreds of MB in memory.
	 *
	 * You may start by adding this component to an Entity and calling either the `AudioSource::LoadSound()` or the `AudioSource::LoadMusic()` method depending on the type of audio you wish to play, in which you must pass the path to your audio file as a parameter.
	 * Note: The path MUST be relative to the executable.
	 *
	 * Loading your audio file starts the audio track right away, but this can be avoided by calling the `AudioSource::Stop()` method right after you load.
	 * You can use `AudioSource::Play()` to start playing a paused track, `AudioSource::Pause()` to pause a track, `AudioSource::Stop()` to completely stop a track.
	 * Now that we've covered the basics, let's get to the fancy 👏 customization 👏 part.
	 * The `AudioSource` component allows for quite a few customizations using the`AudioSource::SetSeek()`, `AudioSource::SetLoop()`, `AudioSource::SetPitch()`, `AudioSource::SetVolume()`, and `AudioSource::SetDistance()` methods - which allow you to set the specific properties. These methods are documented themselves so there's no need to explain them here.
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
		AudioSource* LoadSound(std::string loadPath);

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
		AudioSource* LoadMusic(std::string loadPath);

		/**
		 * @brief Pause the currently playing sound.
		 */
		AudioSource* Pause();

		/**
		 * @brief Continue playing the currently paused sound.
		 */
		AudioSource* Play();

		/**
		 * @brief Stop the currently playing sound.
		 */
		AudioSource* Stop();

		/**
		 * @brief Set the seek to/Move to a specific time (denoted in seconds).
		 *
		 * @param seconds The number of seconds to seek to.
		 */
		AudioSource* SetSeek(float seconds);

		/**
		 * @brief Get the time the seek/player is currently on (denoted in seconds).
		 *
		 * @return `float` The time the seek/player is currently on (denoted in seconds).
		 */
		float GetSeek();

		/**
		 * @brief Set if the sound must loop or not once it ends.
		 *
		 * @param loop If the sound must loop or not once it ends.
		 */
		AudioSource* SetLoop(bool loop);

		/**
		 * @brief Get if the sound is set to loop or not once it ends.
		 *
		 * @return `bool` If the sound is set to loop or not once it ends.
		 */
		bool GetLoop();

		/**
		 * @brief Set the pitch of the sound.
		 *
		 * @param pitch The pitch of the sound.
		 */
		AudioSource* SetPitch(float pitch);

		/**
		 * @brief Get the pitch of the sound.
		 *
		 * @return `float` The pitch of the sound.
		 */
		float GetPitch();

		/**
		 * @brief Set the volume of the sound.
		 *
		 * @param volume The volume of the sound.
		 */
		AudioSource* SetVolume(float volume);

		/**
		 * @brief Get the volume of the sound.
		 *
		 * @return `float` The volume of the sound.
		 */
		float GetVolume();

		/**
		 * @brief Set the distance the sound must be played from, if spatial audio
		 * is enabled using AudioSource::setSpatial(true).
		 *
		 * @param distance The distance the sound must be played from.
		 */
		AudioSource* SetDistance(float distance);

		/**
		 * @brief Get the distance the sound must be played from, if spatial audio
		 * is enabled using AudioSource::setSpatial(true).
		 *
		 * @return `float` The distance the sound must be played from.
		 */
		float GetDistance();

		/**
		 * @brief Set if the sound is spatial or not.
		 *
		 * @param spatial If the sound is spatial or not.
		 */
		AudioSource* SetSpatial(bool spatial);

		/**
		 * @brief Get if the sound is spatial or not.
		 *
		 * @return `bool` If the sound is spatial or not.
		 */
		bool GetSpatial();

		/**
		 * @cond section label="inherited from BehaviourScript"
		 */
		void OnApplicationClose();
		/**
		 * @endcond
		 */
	};
}

#endif