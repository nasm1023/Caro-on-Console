#include "View.h"
#include "Data.h"
#include "Model.h"
#include "Control.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void TextColor(int x) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void SetConsoleBlank() {
	int h = HEIGHT, w = WIDTH;
	TextColor(WHITE);
	for (int i = 0; i < h; i++) {
		GotoXY(0, i);
		for (int j = 0; j < w; j++)
			cout << SPACE;
	}
	GotoXY(0, 0);
}

int GetCurrentColor() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	WORD textAttributes = consoleInfo.wAttributes;
	return textAttributes;
}

void DrawBoard(int r, int c, int x, int y, int color) {
	int tmp = GetCurrentColor();
	GotoXY(x, y);
	TextColor(color);

	// top row
	cout << TOP_LEFT << H_LINE << H_LINE << H_LINE;
	for (int i = 1; i < c; i++) {
		cout << TOP_CROSS << H_LINE << H_LINE << H_LINE;
	}
	cout << TOP_RIGHT;
	GotoXY(x, y + 1);
	for (int i = 0; i <= c; i++) {
		cout << V_LINE << SPACE << SPACE << SPACE;
	}

	// all the middle row
	for (int i = 1; i < r; i++) {
		GotoXY(x, y + i * 2);
		cout << LEFT_CROSS << H_LINE << H_LINE << H_LINE;
		for (int j = 1; j < c; j++)
			cout << CROSS << H_LINE << H_LINE << H_LINE;
		cout << RIGHT_CROSS;
		GotoXY(x, y + i * 2 + 1);
		for (int j = 0; j <= c; j++) {
			cout << V_LINE << SPACE << SPACE << SPACE;
		}
	}

	// bottom row
	GotoXY(x, y + 2 + 2 * (r - 1));
	cout << BOTTOM_LEFT << H_LINE << H_LINE << H_LINE;
	for (int i = 1; i < c; i++) {
		cout << BOTTOM_CROSS << H_LINE << H_LINE << H_LINE;
	}
	cout << BOTTOM_RIGHT;
	TextColor(tmp);
}

//void DrawBox(int w, int h, int dx, int dy, int color) {
//	int tmp = GetCurrentColor();
//
//	// w, h, dy are box's width, box's height, delta x and y (how many column/row will the box be Moved off center) 
//	TextColor(color);
//	GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 - h / 2 + dy);
//	cout << BOX_TOP_LEFT;
//	for (int i = 1; i < w - 1; i++)
//		cout << BOX_H_LINE;
//	cout << BOX_TOP_RIGHT;
//
//	for (int i = 1; i < h - 1; i++) {
//		GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 - h / 2 + i + dy);
//		cout << BOX_V_LINE;
//		for (int j = 1; j < w - 1; j++)
//			cout << SPACE;
//		//GotoXY(WIDTH / 2 + w / 2 - 1 + dx, HEIGHT / 2 - h / 2 + i + dy);
//		cout << BOX_V_LINE;
//	}
//
//	GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 + h / 2 - 1 + dy);
//	cout << BOX_BOTTOM_LEFT;
//	for (int i = 1; i < w - 1; i++)
//		cout << BOX_H_LINE;
//	cout << BOX_BOTTOM_RIGHT;
//
//	TextColor(tmp);
//}

void DrawBox(int w, int h, int x, int y, int color) {
	TextColor(color);
	GotoXY(x, y);
	cout << BOX_TOP_LEFT;
	for (int i = 1; i < w - 1; i++)
	{
		cout << BOX_H_LINE;
		Sleep(5);
	}

	cout << BOX_TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, i + y);
		cout << BOX_V_LINE;
		for (int j = 1; j < w - 1; j++)
			cout << SPACE;
		cout << BOX_V_LINE;
		Sleep(5);
	}

	GotoXY(x, h + y - 1);
	cout << BOX_BOTTOM_LEFT;
	for (int i = w - 1; i > 1; i--)
	{
		cout << BOX_H_LINE;
		Sleep(5);
	}
	cout << BOX_BOTTOM_RIGHT;
}

void PrintCARO(int x, int y, int color)
{
	TextColor(color);
	unsigned char logo[] = { 32, 32, 220, 219, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219, 219, 32, 32, 32, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219, 219, 219, 32, 32,
							219, 219, 32, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 32, 219, 219,
							219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 32, 219, 219,
							219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 219, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219, 219, 32, 32, 32, 219, 219, 32, 32, 32, 32, 32, 219, 219,
							219, 219, 32, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 32, 219, 219,
							32, 32, 219, 219, 219, 219, 219, 32, 32, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 32, 32, 219, 219, 219, 219, 219, 32, 32 };
	int num_lines = 6, num_chars = 37;
	for (int i = 0; i < num_lines; i++)
	{
		GotoXY(x, i + y);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i * num_chars + j]);
	}
}

void PrintNote(int x, int y, int color)
{
	TextColor(color);
	GotoXY(x, y);
	unsigned char Note[] = { 179, 32, 80, 114, 111, 106, 101, 99, 116, 32, 98, 121, 32, 71, 114, 111, 117, 112, 32, 49, 51, 32, 45, 32, 50, 50, 67, 84, 84, 52, 32, 72, 67, 77, 85, 83, 32, 179 };
	for (int i = 0; i < 38; i++)
	{
		cout << Note[i];
		Sleep(10);
	}

}

void DrawHeart(int x, int y, int color)
{
	TextColor(color);
	unsigned char pattern = 3;
	for (int i = 0; i < 30; i = i + 6)
	{
		GotoXY(y, x + i);
		putchar(pattern);
	}
}

void DrawDiamond(int x, int y, int color)
{
	TextColor(color);
	unsigned char pattern = 4;
	for (int i = 0; i < 30; i = i + 6)
	{
		GotoXY(y, x + i);
		putchar(pattern);
	}
}

void BackGround()
{
	DrawHeart(1, 6, LIGHT_RED);
	DrawDiamond(4, 24, MAGENTA);
	DrawHeart(1, 42, LIGHT_RED);
	DrawDiamond(4, 60, MAGENTA);
	DrawHeart(1, 78, LIGHT_RED);
	DrawDiamond(4, 96, MAGENTA);
	DrawHeart(1, 114, LIGHT_RED);

}

void DrawBoxMini(int w, int h, int x, int y, int color)
{
	TextColor(color);
	GotoXY(x, y);
	cout << TOP_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << H_LINE;
	cout << TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, i + y);
		cout << V_LINE;
		for (int j = 1; j < w - 1; j++)
			cout << SPACE;
		cout << V_LINE;
	}

	GotoXY(x, h + y - 1);
	cout << BOTTOM_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << H_LINE;
	cout << BOTTOM_RIGHT;
}

void DrawButton()
{
	DrawBoxMini(14, 3, 89, 6, BLUE);
	GotoXY(94, 7);
	cout << "PLAY";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 9, BLUE);
	GotoXY(94, 10);
	cout << "LOAD";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 12, BLUE);
	GotoXY(94, 13);
	cout << "HELP";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 15, BLUE);
	GotoXY(93, 16);
	cout << "SETTING";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 18, BLUE);
	GotoXY(94, 19);
	cout << "EXIT";
	Sleep(200);
}

void CaroAnimation()
{
	PrintCARO(24, 6, MAGENTA);
	Sleep(150);
	PrintCARO(24, 6, YELLOW);
	Sleep(150);
	PrintCARO(24, 6, LIGHT_CYAN);
	Sleep(150);
	PrintCARO(24, 6, GREEN);
	Sleep(150);
	PrintCARO(24, 6, BLUE);
	Sleep(150);
	PrintCARO(24, 6, LIGHT_YELLOW);
	Sleep(150);
	PrintCARO(24, 6, RED);
}

void MainScreen() {
	BackGround();

	DrawBox(60, 23, 12, 3, GREEN);
	Sleep(500);
	CaroAnimation();
	Sleep(500);
	PrintNote(24, 23, MAGENTA);
	Sleep(500);
	DrawButton();
}

void MainMenu()
{
	SetConsoleBlank();
	MainScreen();
}

int ProcessFinish(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, bool& _TURN, int pWhoWin)
{
	GotoXY(0, _A[B_SIZE - 1][B_SIZE - 1].y + 2);
	switch (pWhoWin) {
	case 1:
		cout << "Nguoi choi O da thang !!!";
		break;
	case -1:
		cout << "Nguoi choi X da thang !!!";
		break;
	case 0:
		cout << "Hai nguoi hoa nhau XOXO";
		break;
	case 2:
		_TURN = !_TURN;
		break;
	}
	GotoXY(_X, _Y);
	return pWhoWin;
}

char AskContinue(_POINT _A[B_SIZE][B_SIZE])
{
	GotoXY(0, _A[B_SIZE - 1][B_SIZE - 1].y + 4);
	cout << "Tiep tuc hay dung lai y/n";
	return toupper(_getch());
}

void AskTurn(bool& _TURN) { // Hỏi lượt đánh trước
	GotoXY(1, 1);
	TextColor(YELLOW);
	cout << "Moi ban chon luot danh truoc: (O/X) ";
	char s = toupper(_getch());
	if (s == 88) {
		_TURN = false;
	}
	else {
		_TURN = true;
	}
}

// Đếm số lượt chơi và in ra màn hình console
void CntTurn(bool& _TURN, int& cntX, int& cntO, bool validEnter) {
	if (_TURN == false && validEnter == true)
	{
		++cntX;
		GotoXY(80, 1);
		cout << "step X:" << cntX;

	}
	else if (_TURN == true && validEnter == true)
	{
		++cntO;
		GotoXY(80, 2);
		cout << "step O:" << cntO;
	}
}

// Hiển thị lượt chơi
void ShowTurn(int _X, int _Y, bool _TURN, bool validEnter)
{
	if (_TURN == true && validEnter == true)
	{
		GotoXY(80, 0);
		cout << "Luot cua X danh !!";
	}
	else if (_TURN == false && validEnter == true)
	{
		GotoXY(80, 0);
		cout << "Luot cua O danh !!";
	}
	GotoXY(_X, _Y);
}

void UnHover(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
	int tmp = GetCurrentColor();
	TextColor(BLUE);
	GotoXY(_A[x][y].x, _A[x][y].y);
	if (_A[x][y].c == 0)
		cout << " ";
	else if (_A[x][y].c == 1) {
		TextColor(O_COLOR);
		cout << "O";
	}
	else {
		TextColor(X_COLOR);
		cout << "X";
	}
	TextColor(tmp);
}

void Hover(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
	int tmp = GetCurrentColor();
	TextColor(BLUE & 15 | BACKGROUND_YELLOW);
	GotoXY(_A[x][y].x, _A[x][y].y);
	if (_A[x][y].c == 0)
		cout << " ";
	else if (_A[x][y].c == 1) {
		TextColor(O_COLOR & 15 | BACKGROUND_YELLOW);
		cout << "O";
	}
	else {
		TextColor(X_COLOR & 15 | BACKGROUND_YELLOW);
		cout << "X";
	}
	TextColor(tmp);
}

// Hàm reset game
void exitGame() {
	system("cls");
}

void HideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void DrawPage(const vector <string>& v, int curPage) {
	int filePerPage = 9;
	int tmp = GetCurrentColor();
	TextColor(YELLOW);
	GotoXY(WIDTH / 2 - 5, HEIGHT / 2 + 8);
	cout << "< ";
	if (curPage <= 9)
		cout << "0";
	cout << curPage << " / ";
	int nPages = ceil(1.0 * v.size() / filePerPage);
	if (nPages <= 9)
		cout << 0;
	cout << nPages << " >";
	TextColor(tmp);

	for (int i = (curPage - 1) * 9, cnt = 1; i < curPage * 9; i++, cnt++) {
		GotoXY(BOX_X + 1, BOX_Y + 2 * cnt - 1);
		for (int j = 1; j < BOX_W - 1; j++)
			cout << " ";
		if (i < v.size()) {
			int n = v[i].size();
			GotoXY(WIDTH / 2 - n / 2, BOX_Y + 2 * cnt - 1);
			Sleep(50);
			cout << v[i];
		}
	}
}

void UnhoverFileName(const vector <string>& v, int curPage, int curFile) {
	int id = 9 * (curPage - 1) + curFile;
	TextColor(CYAN);
	GotoXY(BOX_X + 1, BOX_Y + 2 * (curFile + 1) - 1);
	for (int j = 1; j < BOX_W - 1; j++)
		cout << " ";
	int n = v[id].size();
	GotoXY(WIDTH / 2 - n / 2, BOX_Y + 2 * (curFile + 1) - 1);
	cout << v[id];
}

void HoverFileName(const vector <string>& v, int curPage, int curFile) {
	int id = 9 * (curPage - 1) + curFile;
	int tmp = GetCurrentColor();
	TextColor(RED & 15 | BACKGROUND_YELLOW);
	GotoXY(BOX_X + 1, BOX_Y + 2 * (curFile + 1) - 1);
	cout << "     --->";
	for (int j = 9; j < BOX_W - 11; j++) 
		cout << " ";
	cout << "<---     ";
	int n = v[id].size();
	GotoXY(WIDTH / 2 - n / 2, BOX_Y + 2 * (curFile + 1) - 1);
	cout << v[id];
	TextColor(tmp);
}

void LoadMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn) {
	// Open the file that contains all the name of the saved games.
	fstream inp;
	inp.open("save\\all_save.txt", ios::in);
	if (inp.fail()) {
		cout << "Can't open file\n";
		return;
	}

	SetConsoleBlank();
	BackGround();
	DrawBox(BOX_W, BOX_H - 1, BOX_X, BOX_Y, GREEN);
	TextColor(CYAN);

	// Get the current save data
	string nameFile;
	int filePerPage = 9;
	vector <string> v;
	while (inp >> nameFile) {
		v.push_back(nameFile);
	}
	int nFiles = v.size();
	int nPages = ceil(1.0 * nFiles / filePerPage);

	int curFile = 0, curPage = 1;
	DrawPage(v, 1);
	HoverFileName(v, 1, 0);
	while (true) {
		int _COMMAND = toupper(_getch());
		PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		if (_COMMAND == ESC) {
			return;
		}
		else if (_COMMAND == 'S') {
			UnhoverFileName(v, curPage, curFile);
			curFile = (curFile + 1) % filePerPage;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = 0;
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == 'W') {
			UnhoverFileName(v, curPage, curFile);
			curFile = (curFile - 1 + filePerPage) % filePerPage;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = nFiles % 9 - 1;
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == 'A') {
			curPage--;
			if (curPage == 0)
				curPage = nPages;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = nFiles % 9 - 1;
			DrawPage(v, curPage);
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == 'D') {
			curPage++;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = nFiles % 9 - 1;
			else if (curPage > nPages)
				curPage = 1;
			DrawPage(v, curPage);
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == ENTER) {
			//LoadData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, v[(curPage - 1) * 9 + curFile]);
			//StartGame(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn);
		}
	}
	inp.close();
}