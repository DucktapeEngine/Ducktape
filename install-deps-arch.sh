#!/bin/bash

DEPS="libx11 libxrandr libxinerama libxcursor libxi mesa libglu1-mesa-dev libassimp-dev"


if [ "$EUID" -ne 0 ]
  then echo "Please run as root to install the required dependencies"
  exit
fi

read -p "Do you want to download dependencies for Wayland or X11?[X/wayland]" DSP
if [ "$DSP" -eq "wayland" ] 
  then DEPS="$DEPS glfw-wayland"
else
  DEPS="$DEPS glfw-x11"
fi

DEPS="libx11 libxrandr libxinerama libxcursor libxi mesa assimp"
echo -e "Installing dependencies... \n$DEPS"
pacman -S $DEPS