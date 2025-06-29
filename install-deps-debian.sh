#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root to install the required dependencies"
  exit
fi

DEPS="libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libglfw3-dev libassimp-dev"
echo -e "Installing dependencies... \n$DEPS"
apt install $DEPS