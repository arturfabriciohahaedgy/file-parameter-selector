#!/bin/sh

# Gets fullpath of window.glade
gladepath=$(realpath ./ui/window.glade)

# OS that is running
os = $(uname -a)

sed -i "s|gladepath = \".*\"|gladepath = \"$gladepath\"|g" ./src/window.c

# TODO: Make a case statement to test on other platforms
