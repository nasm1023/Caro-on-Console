#pragma once
#include "Data.h"

void ResetData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO);
bool CheckFullBoard(_POINT _A[B_SIZE][B_SIZE]);
void SetupGame(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int cntWinO, int cntLoseO, int cntDraw);
int TestBoard(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int& cntWinO, int& cntLoseO, int& cntDraw, bool check);
bool CheckWin(_POINT _A[B_SIZE][B_SIZE], int x, int y);
bool CheckWinLose(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int cX, int cY);
int CheckBoard(_POINT _A[B_SIZE][B_SIZE], bool _TURN, int pX, int pY);
void StartGame(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool& sound, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn);
bool LoadData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, string FileName);
bool SaveData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, string FileName);
void LoadSound(bool& sound);
void SetSound(bool& sound, bool value);