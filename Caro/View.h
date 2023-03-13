#pragma once
#include <Windows.h>
#include "Data.cpp"
#include <iostream>
using namespace std;

void FixConsoleWindow();
void SetConsoleBlank();
void DrawBoard(int row, int col, int x, int y, int color);
void TextColor(int x);
int GetCurrentColor();
void DrawBox(int w, int h, int x, int y, int color);
void PrintCARO(int x, int y, int color);
void PrintNote(int x, int y, int color);
void DrawHeart(int x, int y, int color);
void DrawDiamond(int x, int y, int color);
void BackGround();
void DrawBoxMini(int w, int h, int dx, int dy, int color);
void DrawButton();
void CaroAnimation();
void MainScreen();
void MainMenu();
void StartGame();
void resetData();
int processFinish(int pWhoWin);
char askContinue();
void drawBoard(int pSize);
int checkBoard(int pX, int pY);
void askTurn();
void cntTurn(bool validEnter);
void showTurn(bool validEnter);
bool checkFullBoard();
int testBoard(bool check);
void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
void UnHover(int x, int y);
void Hover(int x, int y);
void setupGame();
bool checkWin(int x, int y);
void exitGame();
bool checkWinLose();