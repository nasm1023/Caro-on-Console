#include "View.h"
#include "Data.h"
#include "Control.h"

_POINT _A[B_SIZE][B_SIZE]; //Ma trận bàn cờ
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y, cX, cY; //Tọa độ hiện hành trên màn hình bàn cờ
int cntX;
int cntO;
int saveTurn = 0;
int cntWinO = 0, cntLoseO = 0;
int cntDraw = 0;

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

void resetData()
{//ham khoi tao du lieu mac dinh ban dau cho ban co
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			_A[i][j].x = i * 4 + LEFT + 6;
			_A[i][j].y = j * 2 + TOP + 2;
			_A[i][j].c = 0;
		}
	}
	_TURN = 1; _COMMAND = -1;
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
	cX = cY = 0;
	cntX = 0;
	cntO = 0;
}

int processFinish(int pWhoWin)
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

char askContinue()
{
	GotoXY(0, _A[B_SIZE - 1][B_SIZE - 1].y + 4);
	cout << "Tiep tuc hay dung lai y/n";
	return toupper(_getch());
}

// Vẽ bảng
void drawBoard(int pSize)
{
	for (int i = 0; i < pSize; i++) {
		for (int j = 0; j < pSize; j++) {
			GotoXY(LEFT + 4 * i, TOP + 2 * j);
			cout << ".";
		}
	}
}

// Kiểm tra dữ liệu tại ô đó và in ra X hoặc O
int checkBoard(int pX, int pY)
{
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true)
					_A[i][j].c = 1; // người chơi thứ nhất đánh O
				else
					_A[i][j].c = -1; // người chơi thứ hai đánh X
				return _A[i][j].c;
			}
		}
	}
	return 0; // Trả về nếu ô đó đã có người đánh
}

void askTurn() { // Hỏi lượt đánh trước
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
void cntTurn(bool validEnter) {
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
void showTurn(bool validEnter)
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

// Kiểm tra xem thử có full bảng chưa
bool checkFullBoard() {
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			if (_A[i][j].c != 0)
				return false;
		}
	}
	return true;
}

// Kiểm tra board trả về giá trị tương ứng để in ra màn hình bằng hàm processFinish
int testBoard(bool check) {
	if (check == true && saveTurn == 1)
	{
		cntWinO++;
		return 1; // trả về 1 nếu O thắng
	}
	else if (check == true && saveTurn == -1)
	{
		cntLoseO++;
		return -1; // trả về -1 nếu X thắng
	}
	else if (check == false && checkFullBoard() == true)
	{
		cntDraw++;
		return 0; // trả về không nếu không có người nào thắng và đã đánh full board
	}
	return 2;
}

void UnHover(int x, int y) {
	int tmp = GetCurrentColor();
	TextColor(BLUE);
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

void Hover(int x, int y) {
	int tmp = GetCurrentColor();
	TextColor(BLUE & 15 | BACKGROUND_YELLOW);
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

void MoveRight()
{
	if (_X < _A[B_SIZE - 1][B_SIZE - 1].x)
	{
		GotoXY(_X, _Y);
		UnHover(cX, cY);
		_X += 4;
		cX++;
		GotoXY(_X, _Y);
		Hover(cX, cY);
	}
}

void MoveLeft() {
	if (_X > _A[0][0].x)
	{
		GotoXY(_X, _Y);
		UnHover(cX, cY);
		_X -= 4;
		cX--;
		GotoXY(_X, _Y);
		Hover(cX, cY);
	}
}

void MoveUp() {
	if (_Y > _A[0][0].y)
	{
		GotoXY(_X, _Y);
		UnHover(cX, cY);
		_Y -= 2;
		cY--;
		GotoXY(_X, _Y);
		Hover(cX, cY);
	}
}

void MoveDown() {
	if (_Y < _A[B_SIZE - 1][B_SIZE - 1].y)
	{
		GotoXY(_X, _Y);
		UnHover(cX, cY);
		_Y += 2;
		cY++;
		GotoXY(_X, _Y);
		Hover(cX, cY);
	}
}

// Hàm bắt đầu game và khởi tạo dữ liệu
void setupGame() {
	SetConsoleBlank();
	resetData();
	askTurn();
	SetConsoleBlank();
	TextColor(BLUE);
	DrawBoard(B_SIZE, B_SIZE, 5, 2, GREEN);
	if (_TURN == true) {
		GotoXY(80, 0);
		cout << "Luot cua O danh";
	}
	else {
		GotoXY(80, 0);
		cout << "Luot cua X danh";
	}
	GotoXY(80, 1);
	cout << "step X:" << cntX;
	GotoXY(80, 2);
	cout << "step O:" << cntO;
	GotoXY(90, 1);
	cout << cntWinO << "/" << cntLoseO << "/" << cntDraw;
	GotoXY(90, 2);
	cout << cntLoseO << "/" << cntWinO << "/" << cntDraw;
	GotoXY(_A[0][0].x, _A[0][0].y);
	Hover(cX, cY);
}

// Hàm duyệt tại vị trí (x,y) và xét quanh điểm đó
bool checkWin(int x, int y) {
	int count = 0;
	int i, j;
	int n = B_SIZE;
	if (_A[y][x].c == 0)
		return false;
	// Kiểm tra hàng ngang
	for (i = x - 4; i <= x; i++) {
		if (i < 0 || i + 4 >= n) continue;
		count = 0;
		for (j = i; j <= i + 4; j++) {
			if (_A[y][j].c == _A[y][x].c) count++;
		}
		if (count == 5) return true;
	}

	// Kiểm tra hàng dọc
	for (i = y - 4; i <= y; i++) {
		if (i < 0 || i + 4 >= n) continue;
		count = 0;
		for (j = i; j <= i + 4; j++) {
			if (_A[j][x].c == _A[y][x].c) count++;
		}
		if (count == 5) return true;
	}

	// kiểm tra đường chéo chính
	for (i = x - 4, j = y - 4; i <= x && j <= y; i++, j++) {
		if (i < 0 || i + 4 >= n || j < 0 || j + 4 >= n) continue;
		count = 0;
		for (int k = 0; k < 5; k++) {
			if (_A[j + k][i + k].c == _A[y][x].c) count++;
		}
		if (count == 5) return true;
	}

	// Kiểm tra đường chéo phụ
	for (i = x - 4, j = y + 4; i <= x && j >= y; i++, j--) {
		if (i < 0 || i + 4 >= n || j >= n || j - 4 < 0) continue;
		count = 0;
		for (int k = 0; k < 5; k++) {
			if (_A[j - k][i + k].c == _A[y][x].c) count++;
		}
		if (count == 5) return true;
	}

	return false;
}

// Hàm reset game
void exitGame() {
	system("cls");
}

// Duyệt toàn BOARD để kiểm tra thắng thua
bool checkWinLose()
{
	int i, j;
	for (int i = 0; i < B_SIZE; i++) {
		for (j = 0; j < B_SIZE; j++) {
			if (checkWin(j, i) == true)
			{
				saveTurn = _A[i][j].c;
				return true;
			}
		}
	}
	return false;
}

void StartGame() {
	setupGame();
	bool validEnter = true, ok = 0;
	while (true) {
		if (ok)
			PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		_COMMAND = toupper(_getch());
		ok = true;
		if (_COMMAND == ESC) {
			exitGame();
			break;
		}
		else {
			// Điều khiển
			int tmp = 0;
			//GotoXY(_X, _Y);
			if (_COMMAND == ENTER) {
				switch (checkBoard(_X, _Y)) {
				case -1:
					GotoXY(_X, _Y);
					tmp = GetCurrentColor();
					TextColor(X_COLOR);
					cout << "X";
					TextColor(tmp);
					break;
				case 1:
					GotoXY(_X, _Y);
					tmp = GetCurrentColor();
					TextColor(O_COLOR);
					cout << "O";
					TextColor(tmp);
					break;
				case 0:
					validEnter = false;
					break;
				}
				showTurn(validEnter);
				cntTurn(validEnter);
				if (validEnter == true) {
					switch (processFinish(testBoard(checkWinLose())))
					{
					case -1:
					case 1:
					case 0:
						if (askContinue() != 'Y') {
							exitGame();
							return;
						}
						else setupGame();
					}
				}
				validEnter = true;
			}
			else if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
		}
	}
}