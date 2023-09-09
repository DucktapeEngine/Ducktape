/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#pragma once

#include <string>
#include <filesystem>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#define DT_EXPORT extern "C" __declspec(dllexport)
#endif
#ifdef __linux__
#include <dlfcn.h>
#define DT_EXPORT extern "C" __attribute__((visibility("default")))
#endif

namespace DT
{
	namespace Platform
	{
		/**
		 * @brief Retrieves the last error message as a string.
		 *
		 * @return A string containing the last error message.
		 */
		std::string GetLastErrorAsString();

		/**
		 * @brief Executes a command.
		 *
		 * @param command The command to execute.
		 */
		void Execute(const std::string command);

		/**
		 * @brief The Module class for loading and managing dynamic libraries.
		 */
		class Module
		{
		public:
			/**
			 * @brief The handle to the loaded module.
			 */
#ifdef _WIN32
			HMODULE module;
#endif
#ifdef __linux__
			void *module;
#endif

			/**
			 * @brief Destructor for the Module class. Unloads the module.
			 */
			~Module();

			/**
			 * @brief Loads a dynamic library from the specified path.
			 *
			 * @param path The path to the dynamic library.
			 */
			void Load(std::filesystem::path path);

			/**
			 * @brief Unloads the dynamic library.
			 */
			void Free();

			/**
			 * @brief Retrieves the address of a symbol from the loaded module.
			 *
			 * @tparam T The type of the symbol.
			 * @param symbolName The name of the symbol.
			 * @return The address of the symbol.
			 */
			template <typename T>
			T GetSymbolAddress(const std::string &symbolName)
			{
#ifdef _WIN32
				return (T)GetProcAddress(module, symbolName.c_str());
#endif
#ifdef __linux__
				return (T)dlsym(module, symbolName.c_str());
#endif
				std::cout << Platform::GetLastErrorAsString() << std::endl;
			}
		};
	}
}