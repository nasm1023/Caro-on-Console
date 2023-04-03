#pragma once
#include "Data.h"

void FixConsoleWindow();
void SetConsoleBlank();
void DrawBoard(int row, int col, int x, int y, int color);
void TextColor(int x);
int GetCurrentColor();
void DrawBoxWithAnimation(int w, int h, int x, int y, int color);
void PrintCARO(int x, int y, int color);
void PrintNote(int x, int y, int color);
void DrawHeart(int x, int y, int color);
void DrawDiamond(int x, int y, int color);
void BackGround();
void DrawBoxMini(int w, int h, int dx, int dy, int color);
void DrawButton();
void CaroAnimation();
void MainScreen();
void MainMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn);
int ProcessFinish(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, bool& _TURN, int pWhoWin);
char AskContinue(_POINT _A[B_SIZE][B_SIZE]);
void AskTurn(bool& _TURN);
void CntTurn(bool& _TURN, int& cntX, int& cntO, bool validEnter);
void ShowTurn(int _X, int _Y, bool _TURN, bool validEnter);
void UnHover(_POINT _A[B_SIZE][B_SIZE], int x, int y);
void Hover(_POINT _A[B_SIZE][B_SIZE], int x, int y);
void HideCursor();
void exitGame();
void DrawPage(const vector <string>& v, int curPage);
void LoadGameMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn);
void UnhoverFileName(const vector <string>& v, int curPage, int curFile);
void HoverFileName(const vector <string>& v, int curPage, int curFile);
void DrawBoxNoAnimation(int w, int h, int x, int y, int color);
void Help1();
void Help2();
void HelpScreen();
void LoadingScreen(int color1, int color2, int color3);
void PrintNote(int x, int y, int color);