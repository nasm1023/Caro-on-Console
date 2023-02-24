#include "View.h"
#include "Data.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	///*HWND consoleWindow = GetConsoleWindow();
	//LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	//style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	//SetWindowLong(consoleWindow, GWL_STYLE, style);*/
	//HWND hwnd = GetConsoleWindow();
	//DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	//style &= ~WS_MAXIMIZEBOX;
	//SetWindowLong(hwnd, GWL_STYLE, style);
	//SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

void DrawBoard(int r, int c, int x, int y, int color) {
	GotoXY(x, y);
	TextColor(CYAN);

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
}

void DrawBox(int w, int h, int dx, int dy, int color) {
	// w, h, dy are box's width, box's height, delta x and y (how many column/row will the box be moved off center) 
	TextColor(color);
	GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 - h / 2 + dy);
	cout << BOX_TOP_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << BOX_H_LINE;
	cout << BOX_TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 - h / 2 + i + dy);
		cout << BOX_V_LINE;
		for (int j = 1; j < w - 1; j++)
			cout << SPACE;
		//GotoXY(WIDTH / 2 + w / 2 - 1 + dx, HEIGHT / 2 - h / 2 + i + dy);
		cout << BOX_V_LINE;
	}

	GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 + h / 2 - 1 + dy);
	cout << BOX_BOTTOM_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << BOX_H_LINE;
	cout << BOX_BOTTOM_RIGHT;
}

void PrintLogo(int x, int y, int color) {
	TextColor(color);
	GotoXY(x, y);
	cout << " ________  ________  ________  ________     ";
	GotoXY(x, 1 + y);
	cout << "|\\   ____\\|\\   __  \\|\\   __  \\|\\   __  \\    ";
	GotoXY(x, 2 + y);
	cout << "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\   ";
	GotoXY(x, 3 + y);
	cout << " \\ \\  \\    \\ \\   __  \\ \\   _  _\\ \\  \\\\\\  \\  ";
	GotoXY(x, 4 + y);
	cout << "  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\\\  \\\\ \\  \\\\\\  \\ ";
	GotoXY(x, 5 + y);
	cout << "   \\ \\_______\\ \\__\\ \\__\\ \\__\\\\ _\\\\ \\_______\\";
	GotoXY(x, 6 + y);
	cout << "    \\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|";
}

void MainMenu() {
	SetConsoleBlank();
	PrintLogo(WIDTH / 2 - 22, 2, YELLOW);
	DrawBox(40, 14, 0, 3, CYAN);
	while (true) {
		if (_kbhit()) {
			char _COMMAND = toupper(_getch());
			cout << _COMMAND;
		}
	}
}