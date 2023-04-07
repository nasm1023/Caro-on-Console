#include "Model.h"
#include "Data.h"
#include "View.h"
#include "Control.h"

void ResetData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO)
{//ham khoi tao du lieu mac dinh ban dau cho ban co
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			_A[i][j].y = i * 2 + 1 + BOARD_Y;
			_A[i][j].x = j * 4 + 2 + BOARD_X;
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

// Kiểm tra board trả về giá trị tương ứng để in ra màn hình bằng hàm processFinish
int TestBoard(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int& cntWinO, int& cntLoseO, int& cntDraw, bool check) {
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
	else if (check == false && CheckFullBoard(_A) == true)
	{
		cntDraw++;
		return 0; // trả về không nếu không có người nào thắng và đã đánh full board
	}
	return 2;
}

// Hàm duyệt tại vị trí (x,y) và xét quanh điểm đó
bool CheckWin(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
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

// Duyệt toàn BOARD để kiểm tra thắng thua
bool CheckWinLose(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int cX, int cY)
{
	if (CheckWin(_A, cX, cY) == true)
	{
		saveTurn = _A[cY][cX].c;
		return true;
	}
	return false;
}

// Kiểm tra xem thử có full bảng chưa
bool CheckFullBoard(_POINT _A[B_SIZE][B_SIZE]) {
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			if (_A[i][j].c != 0)
				return false;
		}
	}
	return true;
}

// Kiểm tra dữ liệu tại ô đó và in ra X hoặc O
int CheckBoard(_POINT _A[B_SIZE][B_SIZE], bool _TURN, int pX, int pY)
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

// Hàm bắt đầu game và khởi tạo dữ liệu
void SetupGame(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int cntWinO, int cntLoseO, int cntDraw) {
	SetConsoleBlank();
	ResetData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO);
	AskTurn(_TURN);
	SetConsoleBlank();
	TextColor(BLUE);
	DrawBoard(B_SIZE, B_SIZE, BOARD_X, BOARD_Y, GREEN);
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
	HoverCell(_A, cY, cX);
}

void StartGame(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool& sound, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn) {
	SetupGame(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw);
	bool validEnter = true, ok = 0;
	while (true) {
		_COMMAND = toupper(_getch());
		if (sound) PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
		ok = true;
		if (_COMMAND == ESC) {
			return;
		}
		else {
			// Điều khiển
			int tmp = 0;
			//GotoXY(_X, _Y);
			if (_COMMAND == ENTER) {
				switch (CheckBoard(_A, _TURN, _X, _Y)) {
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
				ShowTurn(_X, _Y, _TURN, validEnter);
				CntTurn(_TURN, cntX, cntO, validEnter);
				if (validEnter == true) {
					switch (ProcessFinish(_A, _X, _Y, _TURN, TestBoard(_A, saveTurn, cntWinO, cntLoseO, cntDraw, CheckWinLose(_A, saveTurn, cX, cY)))) {
					case -1:
					case 1:
					case 0:
						if (AskContinue(_A) != 'Y') {
							ExitGame();
							return;
						}
						else 
							SetupGame(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw);
					}
				}
				validEnter = true;
			}
			else if (_COMMAND == 'A') MoveLeft(_A, _X, _Y, cX, cY);
			else if (_COMMAND == 'W') MoveUp(_A, _X, _Y, cX, cY);
			else if (_COMMAND == 'S') MoveDown(_A, _X, _Y, cX, cY);
			else if (_COMMAND == 'D') MoveRight(_A, _X, _Y, cX, cY);
		}
	}
}

bool LoadData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, string FileName) {
	fstream inp;
	inp.open("save\\data\\" + FileName, ios::in);
	if (inp.fail()) {
		inp.close();
		return 0;
	}
	ResetData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO);
	for (int i = 0; i < B_SIZE; i++)
		for (int j = 0; j < B_SIZE; j++)
			inp >> _A[i][j].c;
	inp >> _TURN >> _COMMAND >> _X >> _Y >> cX >> cY;
	inp >> cntX >> cntO >> cntWinO >> cntLoseO >> cntDraw >> saveTurn;
	inp.close();
	return 1;
}

bool SaveData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, string FileName) {
	fstream out;
	out.open("save\\data\\" + FileName, ios::out);
	if (out.fail()) {
		out.close();
		return 0;
	}
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++)
			out << _A[i][j].c << ' ';
		out << endl;
	}
	out << _TURN << ' ' << _COMMAND << ' ' << _X << ' ' << _Y << ' ' << cX << ' ' << cY << endl;
	out << cntX << ' ' << cntO << ' ' << cntWinO << ' ' << cntLoseO << ' ' << cntDraw << ' ' << saveTurn;
	out.close();
	return 1;
}

void LoadSound(bool& sound) {
	fstream inp;
	inp.open(SOUND_PATH, ios::in);
	if (inp.fail()) {
		cout << "Can't open file";
		return;
	}
	inp >> sound;
	inp.close();
}

void SetSound(bool& sound, bool value) {
	fstream out;
	out.open(SOUND_PATH, ios::out);
	if (out.fail()) {
		cout << "Can't open file";
		return;
	}
	sound = value;
	out << sound;
	out.close();
}