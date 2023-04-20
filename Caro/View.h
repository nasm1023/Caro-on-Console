#pragma once
#include "Data.h"

void FixConsoleWindow();
void SetConsoleBlank();
void DrawBoard(int row, int col, int x, int y, int color);
void TextColor(int x);
int GetCurrentColor();
void DrawBox(int w, int h, int x, int y, int color, int Time);
void PrintCARO(int x, int y, int color);
void PrintNote(int x, int y, int color);
void DrawHeart(int x, int y, int color);
void DrawDiamond(int x, int y, int color);
void BackGround();
void DrawBoxMini(int w, int h, int x, int y, int color);
void DrawButton();
void CaroAnimation();
void MainScreen();
void MainMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, WinningPos WP[5]);
void ascii_art(string input, int x, int y, int t_color);
int ProcessFinish(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, bool& _TURN, int pWhoWin, string& NamePlayer_O, string& NamePlayer_X, WinningPos WP[5]);
char AskContinue(_POINT _A[B_SIZE][B_SIZE]);
void AskTurn(bool& _TURN, bool sound[], string& NamePlayer_O, string& NamePlayer_X);
void CntTurn(bool& _TURN, int& cntX, int& cntO, bool validEnter);
void ShowTurn(int _X, int _Y, bool _TURN, bool validEnter);
void UnHoverCell(_POINT _A[B_SIZE][B_SIZE], int x, int y);
void HoverCell(_POINT _A[B_SIZE][B_SIZE], int x, int y);
void HideCursor(bool ok);
void DrawSaveFilesPage(const vector <string>& v, int curPage, int filesPerPage);
void LoadGameMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, WinningPos WP[5]);
void Help1();
void Help2();
void HelpScreen(bool sound[]);
void LoadingScreen(int color1, int color2, int color3);
void PrintNote(int x, int y, int color);
void DrawCaroBox(int w, int h, int x, int y, int Time);
void SettingMenu(bool sound[]);
string getFileContents(ifstream& File);
void VeO1(int x, int y, int color);
void VeO2(int x, int y, int color);
void VeX1(int x, int y, int color);
void VeX2(int x, int y, int color);
void TurnX();
void TurnO();
void DrawAsciiFile(int x, int y, string nameFile, int color);
void EnterNamePlayer(string& NamePlayer_O, string& NamePlayer_X);
void changeFont(int x);
void DrawTimer(float time, bool _TURN);
void DrawNumber(int x, int y, int number, int color);
void DrawBanner(int x, int y, int color);
void DrawTimerBox(bool _TURN);
void DrawGameInfo(_POINT _A[B_SIZE][B_SIZE], bool _TURN, int _X, int _Y, int cX, int cY, int cntWinO, int cntLoseO, int cntRound);
void DrawScoreBoard(bool _TURN, int _X, int _Y, int cntWinO, int cntLoseO, int cntRound);
void ClearBox(int w, int h, int x, int y);
void HoverButton(_BUTTON a);
void UnhoverButton(_BUTTON a, int color);
bool LoadGameInPauseMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, float& lastPressed, WinningPos WP[5]);
void DrawSaveFilesPageInPauseMenu(const vector <_BUTTON>& v, int curPage, int filesPerPage);
void DrawXWin();
void DrawOWin();
void SetOWin(string NamePlayer_O, WinningPos WP[5], _POINT _A[B_SIZE][B_SIZE]);
void SetXWin(string NamePlayer_X, WinningPos WP[5], _POINT _A[B_SIZE][B_SIZE]);
void Draw(int x, int y, string nameFile, int color);
