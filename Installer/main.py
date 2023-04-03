# Ducktape | An open source C++ 2D & 3D game Engine that focuses on being fast, and powerful.
# Copyright (C) 2022 Aryan Baburajan
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
# 
# In case of any further questions feel free to contact me at
# the following email address:
# aryanbaburajan2007@gmail.com

import subprocess
import requests
import os
import zipfile
import shutil

HEADER = '\033[95m'
BLUE = '\033[94m'
CYAN = '\033[96m'
SUCCESS = '\033[92m'
WARNING = '\033[93m'
FAIL = '\033[91m'
END = '\033[0m'
BOLD = '\033[1m'
UNDERLINE = '\033[4m'

def install():
    # welcome
    print(f"{UNDERLINE}{BOLD}Welcome to Ducktape installer.{END}")
    input("Press enter to continue...")

    # ensure modules
    required_modules = 1

    # cmake
    print(f"Assuring CMake installation {HEADER}(Recommended >v3.25)...{END}")
    try:
        cmake = subprocess.run(['cmake', '--version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        cmake_version = cmake.stdout.decode().splitlines()[0].split()[-1]
        print(f"{SUCCESS}CMake found: v{cmake_version}{END}")
        required_modules-=1
    except subprocess.CalledProcessError as e:
        print(f"{FAIL}CMake not installed.{END}")

    if required_modules > 0:
        print(f"{FAIL}Pending installation of required modules ... please retry after installing.{END}")
        return
    
    # ensuring it has not been cloned before
    directory = "Ducktape"
    if os.path.exists(directory):
        shutil.rmtree(directory)
    
    # cloning the source code
    print(f"{BOLD}Which version would you like to install?{END}")
    print("1. Dev")
    print("2. Latest")

    choice = 0
    while choice != "1" and choice != "2":
        choice = input()
        if choice == "1":
            print("Cloning the dev source code...")

            # get the archive url of the latest commit in main
            commit_url = "https://api.github.com/repos/DucktapeEngine/Ducktape/commits/main"
            commit_response = requests.get(commit_url)
            commit_sha = commit_response.json()["sha"]
            archive_url = "https://github.com/DucktapeEngine/Ducktape/archive/refs/heads/main.zip"

            # download the source code archive
            print(f"Downloading archive from {archive_url}...")
            archive_response = requests.get(archive_url)
            with open("temp.zip", "wb") as f:
                f.write(archive_response.content)

            # extract the source code archive
            print("Extracting archive...")
            with zipfile.ZipFile("temp.zip", "r") as archive:
                archive.extractall(os.getcwd())

            # delete the temporary file
            print("Cleaning up...")
            os.rename("Ducktape-main", "Ducktape")
            os.remove("temp.zip")

        elif choice == "2":
            print("Cloning the latest release' source code...")

            # make a request to the GitHub API to get the latest release information
            url = "https://api.github.com/repos/DucktapeEngine/Ducktape/releases/latest"
            print(f"Downloading archive from {url}...")
            response = requests.get(url, stream=True)
            zip_url = response.json()["zipball_url"]
            zip = requests.get(zip_url, stream=True)

            # download the asset to a temporary file
            with open("temp.zip", "wb") as f:
                for chunk in zip.iter_content(chunk_size=1024):
                    f.write(chunk)

            # extract the contents of the zip file to a directory
            print("Extracting archive...")
            with zipfile.ZipFile("temp.zip", "r") as zip_ref:
                zip_ref.extractall(os.getcwd())

            # delete the temporary file
            print("Cleaning up...")
            for dir in os.listdir('.'):
                if dir.startswith('DucktapeEngine'):
                    os.rename(dir, "Ducktape")
                    break
            os.remove("temp.zip")

        else:
            print("Invalid choice. Please enter 1 or 2.")

    print("Building...")

    os.chdir("Ducktape")
    if not os.path.exists('Build'):
        os.mkdir('Build')
    os.chdir("Build")
    cmake_command = input("Specify CMake configuration command.\n(cmake -G \"MinGW Makefiles\" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=RELEASE ..)\n")
    with subprocess.Popen(cmake_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=1, universal_newlines=True) as p:
        for line in p.stdout:
            print(line, end='')
        for line in p.stderr:
            print(line, end='')
    if p.returncode != 0:
        print("Cmake configuration failed.")
        return
    
    print(f"{HEADER}> cmake --build .{END}")
    with subprocess.Popen(["cmake", "--build", "."], stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=1, universal_newlines=True) as p:
        for line in p.stdout:
            print(line, end='')
        for line in p.stderr:
            print(line, end='')
    if p.returncode != 0:
        print("Cmake build failed.")
        return
    print(f"{BOLD}Installation finished.{END}")
    
if __name__ == "__main__":
    install()