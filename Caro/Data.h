#pragma once

// Included libraries
#include <iostream>
#include <cctype>
#include <Windows.h>
#include <conio.h>

// Namespace
using namespace std;

// Console size
#define WIDTH 120
#define HEIGHT 30

// Board size
#define B_SIZE 12

// Color code
#define BLUE ((15 << 4) | 1)
#define GREEN ((15 << 4) | 2)
#define CYAN ((15 << 4) | 3)
#define RED ((15 << 4) | 4)
#define MAGENTA ((15 << 4) | 5)
#define YELLOW ((15 << 4) | 6)
#define WHITE ((15 << 4) | 7)
#define GRAY ((15 << 4) | 8)
#define LIGHT_BLUE ((15 << 4) | 9)
#define LIGHT_GREEN ((15 << 4) | 10)
#define LIGHT_CYAN ((15 << 4) | 11)
#define LIGHT_RED ((15 << 4) | 12)
#define LIGHT_MAGENTA ((15 << 4) | 13)
#define LIGHT_YELLOW ((15 << 4) | 14)
#define BRIGHT_WHITE ((15 << 4) | 15)

// ASCII code
// special key
#define ENTER 13
#define ESC 27
// for drawing the caro table
#define BOARD_H_LINE (char)196
#define BOARD_V_LINE (char)179
#define BOARD_CROSS (char)197
#define BOARD_TOP_LEFT (char)218
#define BOARD_TOP_RIGHT (char)191
#define BOARD_BOTTOM_LEFT (char)192
#define BOARD_BOTTOM_RIGHT (char)217
#define BOARD_TOP_CROSS (char)194
#define BOARD_BOTTOM_CROSS (char)193
#define	BOARD_LEFT_CROSS (char)195
#define BOARD_RIGHT_CROSS (char)180
// for drawing boxes (menu, etc.)
#define BOX_TOP_LEFT (char)201
#define BOX_TOP_RIGHT (char)187
#define BOX_BOTTOM_LEFT (char)200
#define BOX_BOTTOM_RIGHT (char)188
#define BOX_V_LINE (char)186
#define BOX_H_LINE (char)205
// moving keys
#define W 87
#define A 65
#define S 83
#define D 68
// others
#define SPACE (char)32

// Data types
struct _POINT {
	int x, y, p;
	// x, y: coordinate
	// p -> {0, 1, 2}, 0: vacant, 1: player X, 2: player O
};