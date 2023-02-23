#pragma once
#include <Windows.h>
#include "Data.cpp"
#include <iostream>
using namespace std;

void FixConsoleWindow();
void GotoXY(int x, int y);
void SetConsoleColor();
void DrawBoard(int row, int col, int width, int height, int x, int y);
void DrawTableLine(int numOfCol, char mainSym, char subSym, int width);
void TextColor(int x);
void MainMenu();
void DrawBox(int w, int h, int dx, int dy, int color);