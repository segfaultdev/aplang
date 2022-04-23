#!/usr/bin/sh

# mute out all that nasty output
gcc -O0 -g -static $(find . -name "*.c") -o a.in -Wall -Wextra -Werror
