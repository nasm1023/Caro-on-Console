#pragma once
#include <Windows.h>
#include "Data.cpp"
#include <iostream>
using namespace std;

void FixConsoleWindow();
void GotoXY(int x, int y);
void SetConsoleBlank();
void DrawBoard(int row, int col, int x, int y, int color);
void TextColor(int x);
void MainMenu();
void DrawBox(int w, int h, int dx, int dy, int color);
void PrintLogo(int x, int y, int color);