#!/bin/sh
[ -n "$1" ] || { echo "usage: $0 file.c" >&2; exit 1; }
# c23 so I'll stick to standard C, and dont lean on gnu extensions
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror -g -O0 -fsanitize=address,undefined -o "${1%.c}" "$1"
