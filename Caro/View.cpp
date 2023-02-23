#include "View.h"
#include "Data.h"

void FixConsoleWindow() {
	/*HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);*/
	HWND hwnd = GetConsoleWindow();
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
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

void SetConsoleColor() {
	int h = HEIGHT, w = WIDTH;
	TextColor(WHITE);
	for (int i = 0; i < h; i++) {
		GotoXY(0, i);
		for (int j = 0; j < w; j++)
			cout << " ";
	}
	GotoXY(0, 0);
}

void DrawTableLine(int numOfCol, char mainSym, char subSym, int width) {
	for (int i = 0; i < numOfCol - 1; i++)
	{
		for (int i = 0; i < width; i++) cout << mainSym;
		cout << subSym;
	}
	for (int i = 0; i < width; i++) cout << mainSym;
}

void DrawBoard(int row, int col, int width, int height, int x, int y) {
	GotoXY(x, y);
	cout << BOARD_TOP_LEFT;
	DrawTableLine(col, BOARD_H_LINE, BOARD_TOP_CROSS, width);
	cout << BOARD_TOP_RIGHT;

	for (int i = 0; i < (row - 1) * (height + 1); i++)
	{
		GotoXY(x, y + i + 1);
		if ((i + 1) % (height + 1) != 0)
		{
			cout << BOARD_V_LINE;
			DrawTableLine(col, SPACE, BOARD_V_LINE, width);
			cout << BOARD_V_LINE;
		}
		else
		{
			cout << BOARD_LEFT_CROSS;
			DrawTableLine(col, BOARD_H_LINE, BOARD_CROSS, width);
			cout << BOARD_RIGHT_CROSS;
		}
	}
	for (int i = 0; i < height; i++)
	{
		GotoXY(x, y + (row - 1) * (height + 1) + 1 + i);
		cout << BOARD_V_LINE;
		DrawTableLine(col, SPACE, BOARD_V_LINE, width);
		cout << BOARD_V_LINE;
	}

	GotoXY(x, y + (row - 1) * (height + 1) + 1 + height);
	cout << BOARD_BOTTOM_LEFT;
	DrawTableLine(col, BOARD_H_LINE, BOARD_BOTTOM_CROSS, width);
	cout << BOARD_BOTTOM_RIGHT;
}

void DrawBox(int w, int h, int dx, int dy, int color) {
	// w, h, dy are box's width, box's height, delta x and y (how many column/row will the box be moved) 
	TextColor(color);
	GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 - h / 2 + dy);
	cout << BOX_TOP_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << BOX_H_LINE;
	cout << BOX_TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 - h / 2 + i + dy);
		cout << BOX_V_LINE;
		GotoXY(WIDTH / 2 + w / 2 - 1 + dx, HEIGHT / 2 - h / 2 + i + dy);
		cout << BOX_V_LINE;
	}

	GotoXY(WIDTH / 2 - w / 2 + dx, HEIGHT / 2 + h / 2 - 1 + dy);
	cout << BOX_BOTTOM_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << BOX_H_LINE;
	cout << BOX_BOTTOM_RIGHT;
}

void MainMenu() {
	SetConsoleColor();
	TextColor(YELLOW);
	int tmp = 2;
	GotoXY(WIDTH / 2 - 22, tmp);
	cout << " ________  ________  ________  ________     ";
	GotoXY(WIDTH / 2 - 22, 1 + tmp);
	cout << "|\\   ____\\|\\   __  \\|\\   __  \\|\\   __  \\    ";
	GotoXY(WIDTH / 2 - 22, 2 + tmp);
	cout << "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\   ";
	GotoXY(WIDTH / 2 - 22, 3 + tmp);
	cout << " \\ \\  \\    \\ \\   __  \\ \\   _  _\\ \\  \\\\\\  \\  ";
	GotoXY(WIDTH / 2 - 22, 4 + tmp);
	cout << "  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\\\  \\\\ \\  \\\\\\  \\ ";
	GotoXY(WIDTH / 2 - 22, 5 + tmp);
	cout << "   \\ \\_______\\ \\__\\ \\__\\ \\__\\\\ _\\\\ \\_______\\";
	GotoXY(WIDTH / 2 - 22, 6 + tmp);
	cout << "    \\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|";

	DrawBox(40, 14, 0, 3, CYAN);
	while (true) {
		if (_kbhit()) {
			char _COMMAND = toupper(_getch());
			cout << _COMMAND;
		}
	}
}