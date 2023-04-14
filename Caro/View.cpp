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

void DrawBox(int w, int h, int x, int y, int color, int Time) {
	int tmp = GetCurrentColor();
	TextColor(color);
	for (int i = 0; i < w / 2; i++) {
		GotoXY(x + w / 2 - i, y);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 + i, y);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	GotoXY(x, y);
	cout << BOX_TOP_LEFT;
	GotoXY(x + w, y);
	cout << BOX_TOP_RIGHT;
	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, y + i);
		cout << BOX_V_LINE;
		for (int j = 1; j < w; j++)
			cout << SPACE;
		cout << BOX_V_LINE;
		Sleep(Time);
	}
	GotoXY(x, y + h - 1);
	cout << BOX_BOTTOM_LEFT;
	GotoXY(x + w, y + h - 1);
	cout << BOX_BOTTOM_RIGHT;
	for (int i = w / 2 - 1; i >= 0; i--) {
		GotoXY(x + w / 2 - i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 + i, y + h - 1);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	TextColor(tmp);
}

//update
void PrintCARO(int x, int y, int color)
{
	TextColor(color);
	unsigned char logo[] = { 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 219, 219, 219, 32, 179, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32 };
	int num_lines = 7, num_chars = 45;
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
	int tmp = GetCurrentColor();
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
	TextColor(tmp);
}

void DrawButton()
{
	DrawBoxMini(14, 3, 89, 6, BLUE);
	GotoXY(94, 7);
	TextColor(BLUE);
	cout << "PLAY";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 9, BLUE);
	GotoXY(94, 10);
	TextColor(BLUE);
	cout << "LOAD";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 12, BLUE);
	GotoXY(94, 13);
	TextColor(BLUE);
	cout << "HELP";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 15, BLUE);
	GotoXY(93, 16);
	TextColor(BLUE);
	cout << "SETTING";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 18, BLUE);
	GotoXY(94, 19);
	TextColor(BLUE);
	cout << "EXIT";
	Sleep(200);
}

void CaroAnimation()
{
	PrintCARO(20, 9, MAGENTA);
	Sleep(150);
	PrintCARO(20, 9, YELLOW);
	Sleep(150);
	PrintCARO(20, 9, LIGHT_CYAN);
	Sleep(150);
	PrintCARO(20, 9, GREEN);
	Sleep(150);
	PrintCARO(20, 9, BLUE);
	Sleep(150);
	PrintCARO(20, 9, LIGHT_YELLOW);
	Sleep(150);
	PrintCARO(20, 9, RED);
}

int ProcessFinish(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, bool& _TURN, int pWhoWin, string& NamePlayer_O, string& NamePlayer_X)
{
	GotoXY(0, _A[B_SIZE - 1][B_SIZE - 1].y + 2);
	switch (pWhoWin) {
	case 1:
		SetConsoleBlank();
		//ascii_art(NamePlayer_O, 1, 1, RED);
		//ascii_art("thang !!!", 1, 8, GREEN);
		/*ascii_art("DrawWinScreen", 1, 5, BLUE);*/
		break;
	case -1:
		SetConsoleBlank();
		//ascii_art(NamePlayer_X, 1, 1, RED);
		//ascii_art("thang !!!", 1, 8, GREEN);
		/*ascii_art("DrawWinScreen", 1, 5,BLUE);*/
		break;
	case 0:
		SetConsoleBlank();
		//ascii_art(" DRAW !!", 1, 5, RED);
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

void DrawBanner(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/Banner.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void AskTurn(bool& _TURN, bool sound[], string& NamePlayer_O, string& NamePlayer_X) { // Hỏi lượt đánh trước
	SetConsoleBlank();
	DrawBoxMini(90, 22, 15, 6, GREEN);//vẽ khung to
	// Vẽ hai ô hiển thị O vs X
	int wide = 20;
	int high = 10;
	int x = 20;
	int y = 10;
	DrawAsciiFile(0, 1, "DrawTurn", BLUE);
	DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnO", GRAY);
	DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnX", GRAY);
	// Vẽ ô hiển thị tên
	int WideBoxName = 30;
	int HighBoxName = 3;
	int X_BoxName = 44;
	int Y_BoxName = 10;
	DrawBoxMini(WideBoxName, HighBoxName, X_BoxName, Y_BoxName, MAGENTA);
	GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
	TextColor(GREEN);
	cout << NamePlayer_O;
	GotoXY(X_BoxName + 1, Y_BoxName + 1);
	TextColor(BLUE);
	cout << (unsigned char)17;
	GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
	TextColor(BLUE);
	cout << (unsigned char)16;
	TextColor(RED);
	bool check = true;
	while (true) {
		char press = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (press == 'D' || press == 'A') {
			if (press == 'D')
			{
				GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
				TextColor(YELLOW);
				cout << (unsigned char)16;
				Sleep(200);
				GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
				TextColor(BLUE);
				cout << (unsigned char)16;
			}
			else if (press == 'A') {
				GotoXY(X_BoxName + 1, Y_BoxName + 1);
				TextColor(YELLOW);
				cout << (unsigned char)17;
				Sleep(200);
				GotoXY(X_BoxName + 1, Y_BoxName + 1);
				TextColor(BLUE);
				cout << (unsigned char)17;
			}
			if (check == true)
			{
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
				for (int i = 0; i < NamePlayer_O.size(); i++)
					cout << ' ';
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_X.size() / 2, Y_BoxName + 1);
				TextColor(GREEN);
				cout << NamePlayer_X;
				check = false;
			}
			else if (check == false) {
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_X.size() / 2, Y_BoxName + 1);
				for (int i = 0; i < NamePlayer_X.size(); i++)
					cout << ' ';
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
				TextColor(GREEN);
				cout << NamePlayer_O;
				check = true;
			}
		}
		else if (press == ENTER) {
			break;
		}
	}
	GotoXY(x, y);
	DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnO", BLUE);
	while (true) {
		unsigned char c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == 'A' || c == 'D') {
			if (c == 'A') {
				if (x == 50) {
					DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnX", GRAY);
					x -= 30;
					DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnO", BLUE);
				}
			}
			else if (c == 'D') {
				if (x == 20) {
					DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnO", GRAY);
					x += 30;
					DrawAsciiFile(x + wide / 2, y + high / 2 - 2, "DrawTurnX", RED);
				}
			}
		}
		else if (c == ENTER) {
			if (x == 20) {
				_TURN = true; // true là lượt của O
				if (check == false)
					swap(NamePlayer_O, NamePlayer_X);
				return;
			}
			else if (x == 50) {
				_TURN = false; // false là lượt của X
				if (check == true)
					swap(NamePlayer_O, NamePlayer_X);
				return;
			}
		}
	}
}

//void EnterNamePlayer(string& NamePlayer_O, string& NamePlayer_X) {
//	SetConsoleBlank();
//	HideCursor(0);
//	DrawAsciiFile(0, 1, "DrawEnterName", BLUE);
//	TextColor(BLUE);
//	GotoXY(11, 11);
//	cout << "Enter Name Player 1 (20 character max): "; 
//	while (true) {
//		getline(cin, NamePlayer_O);
//		if (NamePlayer_O.size() <= 20)
//			break;
//		GotoXY(51, 11);
//		for (int i = 0; i < NamePlayer_O.size(); i++)
//			cout << ' ';
//		GotoXY(51, 11);
//	}
//
//	GotoXY(11, 12);
//	cout << "Enter Name Player 2 (20 character max): "; 
//	while (true) {
//		getline(cin, NamePlayer_X);
//		if (NamePlayer_X.size() <= 20)
//			break;
//		GotoXY(51, 12);
//		for (int i = 0; i < NamePlayer_X.size(); i++)
//			cout << ' ';
//		GotoXY(51, 12);
//	}
//	HideCursor(1);
//}

void DrawEnterName(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/DrawEnterName.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void EnterNamePlayer(string& NamePlayer_O, string& NamePlayer_X) {
	unsigned char x = 16;
	SetConsoleBlank();
	HideCursor(0);
	DrawBanner(15, 2, RED);
	DrawEnterName(30, 3, MAGENTA);
	TextColor(GRAY);
	GotoXY(50, 27);
	cout << "< 20 character max >";
	TextColor(BLUE);
	DrawBoxMini(49, 3, 35, 14, GREEN);
	GotoXY(51, 13); cout << " Player 1's Name ";
	DrawBoxMini(49, 3, 35, 19, GREEN);
	GotoXY(51, 18); cout << " Player 2's Name ";
	TextColor(RED);
	GotoXY(48, 15); cout << x;
	GotoXY(48, 20); cout << x;
	while (true) {
		GotoXY(53, 15);
		getline(cin, NamePlayer_O);
		if (NamePlayer_O.size() <= 20)
			break;
		GotoXY(53, 15);
		for (int i = 0; i < NamePlayer_O.size(); i++)
			cout << ' ';
		GotoXY(53, 15);
	}
	while (true) {
		GotoXY(53, 20);
		getline(cin, NamePlayer_X);
		if (NamePlayer_X.size() <= 20)
			break;
		GotoXY(53, 20);
		for (int i = 0; i < NamePlayer_X.size(); i++)
			cout << ' ';
		GotoXY(53, 20);
	}
	HideCursor(1);
}

// Đếm số lượt chơi và in ra màn hình console
void CntTurn(bool& _TURN, int& cntX, int& cntO, bool validEnter) {
	if (_TURN == false && validEnter == true)
		++cntX;
	else if (_TURN == true && validEnter == true)
		++cntO;
}

// Hiển thị lượt chơi
void ShowTurn(int _X, int _Y, bool _TURN, bool validEnter)
{
	int tmp = GetCurrentColor();
	TextColor(CYAN);
	if (_TURN == true && validEnter == true)
	{
		TurnX();
	}
	else if (_TURN == false && validEnter == true)
	{
		TurnO();
	}
	GotoXY(_X, _Y);
	TextColor(tmp);
}

void UnHoverCell(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
	int tmp = GetCurrentColor();
	TextColor(BLUE);
	GotoXY(_A[x][y].x - 1, _A[x][y].y);
	if (_A[x][y].c == 0)
		cout << "   ";
	else if (_A[x][y].c == 1) {
		TextColor(O_COLOR);
		cout << " O ";
	}
	else {
		TextColor(X_COLOR);
		cout << " X ";
	}
	TextColor(tmp);
}

void HoverCell(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
	int tmp = GetCurrentColor();
	//TextColor(BLUE & 15 | BACKGROUND_YELLOW);
	TextColor(YELLOW);
	GotoXY(_A[x][y].x - 1, _A[x][y].y);
	if (_A[x][y].c == 0)
		cout << L_TRIANGLE << " " << R_TRIANGLE;
	else if (_A[x][y].c == 1) {
		cout << L_TRIANGLE;
		//TextColor(O_COLOR & 15 | BACKGROUND_YELLOW);
		TextColor(O_COLOR);
		cout << "O";
		TextColor(YELLOW);
		cout << R_TRIANGLE;
	}
	else {
		cout << L_TRIANGLE;
		//TextColor(X_COLOR & 15 | BACKGROUND_YELLOW);
		TextColor(X_COLOR);
		cout << "X";
		TextColor(YELLOW);
		cout << R_TRIANGLE;
	}
	TextColor(tmp);
}

void HideCursor(bool ok) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = !ok;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void DrawSaveFilesPage(const vector <string>& v, int curPage) {
	int filePerPage = 9;
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

	TextColor(CYAN);
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
	cout << "        " << L_TRIANGLE;
	for (int j = 9; j < BOX_W - 11; j++) 
		cout << " ";
	cout << R_TRIANGLE << "        ";
	int n = v[id].size();
	GotoXY(WIDTH / 2 - n / 2, BOX_Y + 2 * (curFile + 1) - 1);
	cout << v[id];
	TextColor(tmp);
}

void LoadGameMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X) {
	// Open the file that contains all the name of the saved games.
	fstream inp;
	inp.open("save\\all_save.txt", ios::in);
	if (inp.fail()) {
		cout << "Can't open file\n";
		return;
	}

	SetConsoleBlank();
	BackGround();
	DrawBox(BOX_W, BOX_H - 1, BOX_X, BOX_Y, GREEN, 1);
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
	DrawSaveFilesPage(v, 1);
	GotoXY(47, 26);
	TextColor(MAGENTA);
	cout << " " << L_TRIANGLE << " PRESS ESC TO COMEBACK " << R_TRIANGLE << " ";
	HoverFileName(v, 1, 0);
	while (true) {
		int _COMMAND = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
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
			DrawSaveFilesPage(v, curPage);
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == 'D') {
			curPage++;
			if (curPage == nPages && curFile + 9 * (curPage - 1) >= nFiles)
				curFile = nFiles % 9 - 1;
			else if (curPage > nPages)
				curPage = 1;
			DrawSaveFilesPage(v, curPage);
			HoverFileName(v, curPage, curFile);
		}
		else if (_COMMAND == ENTER) {
			LoadData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, v[(curPage - 1) * 9 + curFile]);
			LoadingScreen(BLUE, GREEN, LIGHT_CYAN);
			StartGame(_A, 0, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X);
			return;
		}
	}
	inp.close();
}

void DrawCaroBox(int w, int h, int x, int y, int Time)
{
	TextColor(GREEN);
	GotoXY(x + w / 2, y);
	for (int i = 0; i < w / 2; i++)
	{
		GotoXY(x + w / 2 + i, y);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 - i, y);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	GotoXY(x, y);
	cout << BOX_TOP_LEFT;
	GotoXY(x + w, y);
	cout << BOX_TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, i + y);
		cout << BOX_V_LINE;
		for (int j = 1; j < w; j++)
			cout << SPACE;
		cout << BOX_V_LINE;
		Sleep(Time);
	}

	GotoXY(x, h + y - 1);
	cout << BOX_BOTTOM_LEFT;
	GotoXY(x + w, h + y - 1);
	cout << BOX_BOTTOM_RIGHT;
	GotoXY(x, y + h - 5);
	cout << BOX_LEFT;
	GotoXY(x + w, y + h - 5);
	cout << BOX_RIGHT;
	for (int i = 1; i <= w / 2; i++)
	{
		GotoXY(x + i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + w - i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + i, y + h - 5);
		cout << BOX_H_LINE;
		GotoXY(x + w - i, y + h - 5);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	DrawBoxMini(58, 13, 14, 6, LIGHT_YELLOW);
	CaroAnimation();
	Sleep(500);
	PrintNote(23, 21, MAGENTA);
}

void MainScreen() {
	BackGround();
	DrawCaroBox(62, 19, 12, 5, 5);
	Sleep(500);
	DrawButton();
}

void MainMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X)
{
	LoadingScreen(BLUE, GREEN, LIGHT_CYAN);
	Sleep(50);
	SetConsoleBlank();
	BackGround();
	MainScreen();

	int x = 94;
	int y = 7;
	DrawBoxMini(14, 3, 89, y - 1, RED);
	GotoXY(x, y); // Đưa cursor tới phím chức năng đầu tiên.
	TextColor(RED);
	cout << "PLAY";
	while (true)
	{
		unsigned char c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == 'W' || c == 'S')
		{
			//c = _getch();
			if (c == 'W')
			{
				if ((y >= 10) && (y <= 19))
				{
					// Đưa lại nút cũ về màu xanh
					DrawBoxMini(14, 3, 89, y - 1, BLUE);
					TextColor(BLUE);
					if (y == 7)
					{
						GotoXY(x, y);
						cout << "PLAY";
					}
					if (y == 10)
					{
						GotoXY(x, y);
						cout << "LOAD";
					}
					if (y == 13)
					{
						GotoXY(x, y);
						cout << "HELP";
					}
					if (y == 16)
					{
						GotoXY(x - 1, y);
						cout << "SETTING";
					}
					if (y == 19)
					{
						GotoXY(x, y);
						cout << "EXIT";
					}
					y = y - 3;
					//Biến nút đang trỏ vào thành màu đỏ 
					DrawBoxMini(14, 3, 89, y - 1, RED);
					TextColor(RED);
					if (y == 7)
					{
						GotoXY(x, y);
						cout << "PLAY";
					}
					if (y == 10)
					{
						GotoXY(x, y);
						cout << "LOAD";
					}
					if (y == 13)
					{
						GotoXY(x, y);
						cout << "HELP";
					}
					if (y == 16)
					{
						GotoXY(x - 1, y);
						cout << "SETTING";
					}
					if (y == 19)
					{
						GotoXY(x, y);
						cout << "EXIT";
					}

				}
			}
			else if (c == 'S')
			{
				if ((y >= 7) && (y <= 16))
				{
					DrawBoxMini(14, 3, 89, y - 1, BLUE);
					TextColor(BLUE);
					if (y == 7)
					{
						GotoXY(x, y);
						cout << "PLAY";
					}
					if (y == 10)
					{
						GotoXY(x, y);
						cout << "LOAD";
					}
					if (y == 13)
					{
						GotoXY(x, y);
						cout << "HELP";
					}
					if (y == 16)
					{
						GotoXY(x - 1, y);
						cout << "SETTING";
					}
					if (y == 19)
					{
						GotoXY(x, y);
						cout << "EXIT";
					}
					y = y + 3;
					DrawBoxMini(14, 3, 89, y - 1, RED);
					TextColor(RED);

					if (y == 7)
					{
						GotoXY(x, y);
						cout << "PLAY";
					}
					if (y == 10)
					{
						GotoXY(x, y);
						cout << "LOAD";
					}
					if (y == 13)
					{
						GotoXY(x, y);
						cout << "HELP";
					}
					if (y == 16)
					{
						GotoXY(x - 1, y);
						cout << "SETTING";
					}
					if (y == 19)
					{
						GotoXY(x, y);
						cout << "EXIT";
					}

				}
			}
		}
		else if ((c == 32) || (c == 13)) // Tương tác với phím bằng cách bấm Enter hoặc Space
		{
			if (y == 7)
			{
				EnterNamePlayer(NamePlayer_O, NamePlayer_X);
				AskTurn(_TURN, sound, NamePlayer_O, NamePlayer_X);
				StartGame(_A, 1, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X);
				return;
			}
			if (y == 10)
			{
				LoadGameMenu(_A, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X);
				return;
			}
			if (y == 13)
			{
				HelpScreen(sound);
				return;
			}
			if (y == 16)
			{
				SettingMenu(sound);
				return;
			}
			if (y == 19)
			{
				ExitGame();
			}
		}
	}
}

//Help1 2 là để nhét dô HelpScreen cho gọn
void Help1()
{
	TextColor(RED);
	GotoXY(20, 7);
	cout << L_TRIANGLE << " RULE " << R_TRIANGLE;
	TextColor(GREEN);
	GotoXY(20, 14);
	cout << L_TRIANGLE << " MOVE " << R_TRIANGLE;
	TextColor(MAGENTA);
	GotoXY(18, 20);
	cout << L_TRIANGLE << " ABOUT US " << R_TRIANGLE;
}

void Help2()
{
	TextColor(RED);
	GotoXY(40, 5);
	cout << "The game is played on a board with 12 rows and 12 columns." << endl;
	GotoXY(40, 7);
	cout << "To win the round, player needs to make a line consisting of 5" << endl;
	GotoXY(40, 8);
	cout << "consecutive pieces horizontally, vertically or diagonally." << endl;
	GotoXY(40, 10);
	cout << "If more than 90% of the board has been marked, the result will ";
	GotoXY(40, 11);
	cout << "be a draw.";
	TextColor(GREEN);
	GotoXY(40, 14);
	cout << "Up: W";
	GotoXY(40, 15);
	cout << "Down: S";
	GotoXY(55, 14);
	cout << "Left: A";
	GotoXY(55, 15);
	cout << "Right: D";
	GotoXY(70, 14);
	cout << "Choose: Enter";
	TextColor(MAGENTA);
	GotoXY(76, 19);
	cout << "Teacher: Truong Toan Thinh";
	GotoXY(76, 20);
	cout << "Group: 13";
	GotoXY(76, 21);
	cout << "22CTT4 - HCMUS";
	GotoXY(40, 18);
	cout << "Dang Duy Lan      -  22120182";
	GotoXY(40, 19);
	cout << "Nguyen Nhat Long  -  22120194";
	GotoXY(40, 20);
	cout << "Hoang Thanh Man   -  22120200";
	GotoXY(40, 21);
	cout << "Ly Truong Nam     -  22120218";
	GotoXY(40, 22);
	cout << "Tran Thao Ngan    -  22120225";
	TextColor(LIGHT_RED);
	GotoXY(47, 26);
	cout << " " << L_TRIANGLE << " PRESS ESC TO COMEBACK " << R_TRIANGLE << " ";
}

void HelpScreen(bool sound[])
{
	SetConsoleBlank();
	DrawBox(98, 25, 11, 2, CYAN, 0);
	DrawBoxMini(94, 23, 13, 3, LIGHT_CYAN);
	for (int i = 0; i < 21; i++)
	{
		GotoXY(34, 4 + i);
		cout << V_LINE;
	}
	Help1();
	Help2();
	while (true) {
		char c = _getch();
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == ESC)
			return;
	}
}

void LoadingScreen(int color1, int color2, int color3) //color 1 la mau khung, 2 la mau chu, 3 la mau cai thanh o giua
{
	SetConsoleBlank();
	unsigned char s = { 219 };
	DrawBoxMini(51, 3, 34, 13, color1);
	GotoXY(55, 17);
	TextColor(color2);
	cout << "LOADING...";
	GotoXY(36, 14);
	for (int i = 0; i < 34; i++)
	{
		TextColor(color3);
		cout << s;
		Sleep(10);
	}
	Sleep(200);
	GotoXY(70, 14);
	for (int i = 0; i < 13; i++)
	{
		TextColor(color3);
		cout << s;
		Sleep(10);
	}
}

void CreateConsoleWindow(int pWidth, int pHeight)
{
	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 240);
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, 0, 0, pWidth, pHeight, TRUE);
}

void changeFont(int x)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = x;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_BOLD;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void SettingMenu(bool sound[]) {
	SetConsoleBlank();
	GotoXY(50, 15);
	int tmp = GetCurrentColor();
	TextColor(RED);
	cout << "Nhan ENTER di! SPACE cung duoc!!";
	TextColor(tmp);
	while (true) {
		char c = _getch();
		if (c == ENTER)
			SetSound(sound, CLICK_SFX, sound[CLICK_SFX] ^ 1);
		else if (c == SPACE)
			SetSound(sound, BGM, sound[BGM] ^ 1);
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == ESC)
			return;
	}
}

void VeX1(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/VeX1.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x, y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void VeX2(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/VeX2.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x, y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void VeO1(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/VeO1.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void VeO2(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/VeO2.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void TurnX() {
	VeO1(95, 5, GRAY);
	VeX2(74, 5, RED);
}

void TurnO() {
	VeO2(95, 5, BLUE);
	VeX1(74, 5, GRAY);
}

string getFileContents(ifstream& File)
{
	string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			string TempLine;                  //Temp line
			getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}

void DrawAsciiFile(int x, int y,string nameFile, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	GotoXY(x, y);
	ifstream Read("assets/UI/" + nameFile + ".txt");
	string Art = getFileContents(Read);
	cout << Art << endl;
	Read.close();
	SetConsoleOutputCP(437);
}

void ShowTimer(float time) {
	time = float(int(time * 100)) / 100;
	//DrawNumber(69, 21, 0, MAGENTA);
	int num[4] = { 0 };
	num[0] = time / 10;
	num[1] = (int)time % 10;
	num[2] = int(time * 10) % 10;
	num[3] = int(time * 100) % 10;
	for (int i = 0; i < 4; i++)
		DrawNumber(68 + i * 10 + 4 * (i > 1), 21, num[i], YELLOW);
}

void DrawNumber(int x, int y, int number, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	string f = "assets/UI/Number/";
	f += char('0' + number);
	f += ".txt";
	ifstream Read(f);
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}