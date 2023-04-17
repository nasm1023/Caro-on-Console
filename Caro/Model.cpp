#include "Model.h"
#include "Data.h"
#include "View.h"
#include "Control.h"

void ResetData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, float& remain)
{//ham khoi tao du lieu mac dinh ban dau cho ban co
	for (int i = 0; i < B_SIZE; i++) {
		for (int j = 0; j < B_SIZE; j++) {
			_A[i][j].y = i * 2 + 1 + BOARD_Y;
			_A[i][j].x = j * 4 + 2 + BOARD_X;
			_A[i][j].c = 0;
		}
	}
	_COMMAND = -1;
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
	cX = cY = 0;
	cntX = 0;
	cntO = 0;
	remain = 15e3;
}

// Kiểm tra board trả về giá trị tương ứng để in ra màn hình bằng hàm processFinish
int TestBoard(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int& cntWinO, int& cntLoseO, int& cntDraw, int& cntRound, bool check) {
	if (check == true && saveTurn == 1)
	{
		if (++cntRound > 9)
			cntRound = 1;
		cntWinO = (cntWinO + 1) % 10;
		return 1; // trả về 1 nếu O thắng
	}
	else if (check == true && saveTurn == -1)
	{
		if (++cntRound > 9)
			cntRound = 1;
		cntLoseO = (cntLoseO + 1) % 10;
		return -1; // trả về -1 nếu X thắng
	}
	else if (check == false && CheckFullBoard(_A) == true)
	{
		if (++cntRound > 9)
			cntRound = 1;
		cntDraw = (cntDraw + 1) % 10;
		return 0; // trả về không nếu không có người nào thắng và đã đánh full board
	}
	return 2;
}

// Hàm duyệt tại vị trí (x,y) và xét quanh điểm đó
bool CheckWin(_POINT _A[B_SIZE][B_SIZE], int x, int y, WinningPos WP[5]) {
	int count = 0;
	int i, j;
	int n = B_SIZE;
	if (_A[y][x].c == 0)
		return false;
	// Kiểm tra hàng ngang
	for (i = x - 4; i <= x; i++) {
		int k = 0;
		if (i < 0 || i + 4 >= n) continue;
		count = 0;
		for (j = i; j <= i + 4; j++) {
			if (_A[y][j].c == _A[y][x].c) count++;
		}
		if (count == 5) {
			for (j = i; j <= i + 4; j++) {
				WP[k].x = y;
				WP[k].y = j;
				k++;
			}
			return true;
		}
	}

	// Kiểm tra hàng dọc
	for (i = y - 4; i <= y; i++) {
		int k = 0;
		if (i < 0 || i + 4 >= n) continue;
		count = 0;
		for (j = i; j <= i + 4; j++) {
			if (_A[j][x].c == _A[y][x].c) count++;
		}
		if (count == 5)
		{
			for (j = i; j <= i + 4; j++) {
				WP[k].x = j;
				WP[k].y = x;
				k++;
			}
			return true;
		}
	}

	// kiểm tra đường chéo chính
	for (i = x - 4, j = y - 4; i <= x && j <= y; i++, j++) {
		int l = 0;
		if (i < 0 || i + 4 >= n || j < 0 || j + 4 >= n) continue;
		count = 0;
		for (int k = 0; k < 5; k++) {
			if (_A[j + k][i + k].c == _A[y][x].c) count++;
		}
		if (count == 5)
		{
			for (int k = 0; k < 5; k++) {
				WP[l].x = j + k;
				WP[l].y = i + k;
				l++;
			}
			return true;
		}
	}

	// Kiểm tra đường chéo phụ
	for (i = x - 4, j = y + 4; i <= x && j >= y; i++, j--) {
		int l = 0;
		if (i < 0 || i + 4 >= n || j >= n || j - 4 < 0) continue;
		count = 0;
		for (int k = 0; k < 5; k++) {
			if (_A[j - k][i + k].c == _A[y][x].c) count++;
		}
		if (count == 5)
		{
			for (int k = 0; k < 5; k++) {
				WP[l].x = j - k;
				WP[l].y = i + k;
				l++;
			}
			return true;
		}
	}

	return false;
}

// Duyệt toàn BOARD để kiểm tra thắng thua
bool CheckWinLose(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int cX, int cY, WinningPos WP[5])
{
	if (CheckWin(_A, cX, cY, WP) == true)
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
void SetupGame(_POINT _A[B_SIZE][B_SIZE], bool reset, bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int cntWinO, int cntLoseO, int cntDraw, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain) {
	SetConsoleBlank();
	if (reset) {
		ResetData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, remain);
	}
	DrawGameInfo(_A, _TURN, _X, _Y, cX, cY, cntWinO, cntLoseO, cntRound);
}

bool EnterName(string& s) {
	char c;
	while (true) {
		c = _getch();
		if (c == ENTER) {
			break;
		}
		else if (c == ESC) {
			s = "";
			return 0;
		}
		else if (c == BACK_SPACE) {
			if (s.size()) {
				int x = whereX(), y = whereY();
				GotoXY(x - 1, y);
				cout << ' ';
				GotoXY(x - 1, y);
				s.pop_back();
			}
		}
		else if (s.size() < 20) {
			cout << c;
			s += c;
		}
	}
	return 1;
}

bool PauseGame(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, float& lastPressed, WinningPos WP[5]) {
	remain += lastPressed - clock();
	ClearBox(49, 15, 64, 4);
	TextColor(BLACK);
	GotoXY(23, 1);
	cout << "PAUSED";
	TextColor(LIGHT_MAGENTA);
	GotoXY(63, 11);
	cout << BOX_V_LINE;
	GotoXY(113, 11);
	cout << BOX_V_LINE;
	//DrawBoxMini(14, 15, 65, 4, LIGHT_MAGENTA);
	for (int i = 0; i < 15; i++) {
		GotoXY(78, 4 + i);
		cout << V_LINE;
	}
	int x = 65, y = 5;
	vector <_BUTTON> button;
	button.resize(5);
	button[0].data = "    SAVE    ";
	button[1].data = "    LOAD    ";
	button[2].data = "   OPTION   ";
	button[3].data = "   RESUME   ";
	button[4].data = "    EXIT    ";
	for (int i = 0; i < button.size(); i++) {
		button[i].x = x;
		button[i].y = y + 3 * i;
	}
	TextColor(BLACK);
	int n = button.size();
	for (int i = 0; i < n; i++) {
		GotoXY(button[i].x, button[i].y);
		cout << button[i].data;
	}
	char c;
	int cur = 0, prv = -1;
	bool ok = 0;
	HoverButton(button[cur]);
	while (true) {
		c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == ESC)
			break;
		else if (c == W || c == S) {
			if (c == W)
				prv = cur--;
			else
				prv = cur++;
			if (cur < 0)
				cur = n - 1;
			if (cur >= n)
				cur = 0;
			UnhoverButton(button[prv], BLACK);
			HoverButton(button[cur]);
		}
		else if (c == ENTER) {
			if (cur == 4) {
				ok = 1;
				break;
			}
			if (cur == 3)
				break;
			if (cur == 1) {
				UnhoverButton(button[cur], BLACK);
				bool ok = LoadGameInPauseMenu(_A, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, lastPressed, WP);
				if (ok)
					return 1;
				ClearBox(34, 15, 79, 4);
				HoverButton(button[cur]);
			}
			else if (cur == 0) {
				UnhoverButton(button[cur], BLACK);
				string fileName = "";
				GotoXY(88, 6);
				TextColor(GREEN);
				cout << "ENTER FILE NAME: ";
				DrawBoxMini(25, 3, 84, 8, BLACK);
				GotoXY(85, 9);
				cout << L_TRIANGLE << ' ';
				HideCursor(0);
				bool ok = EnterName(fileName);
				if (ok) {
					fileName += ".txt";
					SaveData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, fileName, remain);
					GotoXY(87, 13);
					cout << "SAVED SUCCESSFULLY!";
				}
				HideCursor(1);
				while (ok) {
					char c = toupper(_getch());
					if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
					break;
				}
				ClearBox(34, 15, 79, 4);
				HoverButton(button[cur]);
			}
		}
	}
	TextColor(BLACK);
	GotoXY(23, 1);
	cout << "      ";
	lastPressed = clock();
	return ok;
}

void StartGame(_POINT _A[B_SIZE][B_SIZE], bool reset, bool& _TURN, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, WinningPos WP[5]) {
	SetupGame(_A, reset, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, cntRound, NamePlayer_O, NamePlayer_X, remain);
	bool validEnter = true;
	float lastPressed = clock();
	while (true) {
		DrawTimer((lastPressed + remain - clock()) / 1000.0, _TURN);
		if (((lastPressed + remain - clock()) / 1000.0) < 0) {
			ShowTurn(_X, _Y, _TURN, 1);
			_TURN = !_TURN;
			DrawTimerBox(_TURN);
			remain = 15e3;
			lastPressed = clock();
		}
		if (_kbhit()) {
			_COMMAND = toupper(_getch());
			if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
			if (_COMMAND == ESC) {
				bool ok = PauseGame(_A, _TURN, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, lastPressed, WP);
				if (ok)
					return;
				DrawScoreBoard(_TURN, _X, _Y, cntWinO, cntLoseO, cntRound);
				continue;
			}
			// Điều khiển
			int tmp = 0;
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
					switch (ProcessFinish(_A, _X, _Y, _TURN, TestBoard(_A, saveTurn, cntWinO, cntLoseO, cntDraw, cntRound, CheckWinLose(_A, saveTurn, cX, cY, WP)), NamePlayer_O, NamePlayer_X, WP)) {
					case -1:
					case 1:
					case 0:
						if (AskContinue(_A) != 'Y') {
							return;
						}
						else {
							SetupGame(_A, 1, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, cntRound, NamePlayer_O, NamePlayer_X, remain);
						}
					}
					DrawTimerBox(_TURN);
					remain = 15e3;
					lastPressed = clock();
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

bool LoadData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, string FileName, float& remain) {
	fstream inp;
	inp.open("save/data/" + FileName, ios::in);
	if (inp.fail()) {
		inp.close();
		return 0;
	}
	ResetData(_A, _TURN, _COMMAND, _X, _Y, cX, cY, cntX, cntO, remain);
	for (int i = 0; i < B_SIZE; i++)
		for (int j = 0; j < B_SIZE; j++)
			inp >> _A[i][j].c;
	inp >> _TURN >> _COMMAND >> _X >> _Y >> cX >> cY;
	inp >> cntX >> cntO >> cntWinO >> cntLoseO >> cntDraw >> saveTurn >> cntRound >> remain;
	inp.ignore();
	getline(inp, NamePlayer_O);
	getline(inp, NamePlayer_X);
	inp.close();
	return 1;
}

bool SaveData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, string FileName, float& remain) {
	fstream out;
	out.open("save/data/" + FileName, ios::out);
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
	out << cntX << ' ' << cntO << ' ' << cntWinO << ' ' << cntLoseO << ' ' << cntDraw << ' ' << saveTurn << ' ' << cntRound << ' ' << remain << endl;
	out << NamePlayer_O << endl << NamePlayer_X;
	out.close();
	out.open("save/all_save.txt", ios::app);
	string s = "";
	bool ok = 0;
	fstream inp;
	inp.open("save/all_save.txt", ios::in);
	while (inp >> s) 
		ok |= (s == FileName);
	if (!ok)
		out << endl << FileName;
	out.close();
	return 1;
}

void LoadSound(bool sound[]) {
	fstream inp;
	inp.open(SOUND_PATH, ios::in);
	if (inp.fail()) {
		cout << "Can't open file";
		return;
	}
	int n = 3;
	for (int i = 0; i < n; i++)
		inp >> sound[i];
	if (sound[BGM])
		PlayAudio(BGM);
	else
		StopSound(BGM);
	inp.close();
}

void SetSound(bool sound[], int type, bool value) {
	fstream out;
	out.open(SOUND_PATH, ios::out);
	if (out.fail()) {
		cout << "Can't open file";
		return;
	}
	sound[type] = value;
	int n = 3;
	for (int i = 0; i < n; i++)
		out << sound[i] << ' ';
	LoadSound(sound);
	out.close();
}

void PlayAudio(int type) {
	if (type == BGM)
		mciSendString(L"play assets/sounds/bgm.wav", NULL, 0, NULL);
		//PlayAudio(TEXT("assets/sounds/bgm.wav"), NULL, SND_ASYNC);
	else if (type == CLICK_SFX)
		//mciSendString(L"play assets/sounds/click_sfx.wav", NULL, 0, NULL);
		PlaySound(TEXT("assets/sounds/click_sfx.wav"), NULL, SND_ASYNC);
	else if (type == WIN_SFX)
		mciSendString(L"play assets/sounds/win_sfx.wav", NULL, 0, NULL);
}

void StopSound(int type) {
	if (type == BGM)
		mciSendString(L"stop assets/sounds/bgm.wav", NULL, 0, NULL);
}

string CleanFileName(string s) {
	int i = 0;
	while (s[i] == ' ')
		i++;
	while (s.back() == ' ')
		//s.erase(s.size() - 1, 1);
		s.pop_back();
	string res = "";
	for (; i < s.size(); i++)
		res += s[i];
	return res;
}

void ExitGame() {
	StopSound(BGM);
	SetConsoleBlank();
	exit(0);
}