#include "View.h"
#include "Data.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
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
		for (int j = 0; j < w; j++)
			cout << " ";
		if (i < 29)
			cout << endl;
	}
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
	cout << TOP_LEFT;
	DrawTableLine(col, H_LINE, TOP_CROSS, width);
	cout << TOP_RIGHT;

	for (int i = 0; i < (row - 1) * (height + 1); i++)
	{
		GotoXY(x, y + i + 1);
		if ((i + 1) % (height + 1) != 0)
		{
			cout << V_LINE;
			DrawTableLine(col, SPACE, V_LINE, width);
			cout << V_LINE;
		}
		else
		{
			cout << LEFT_CROSS;
			DrawTableLine(col, H_LINE, CROSS, width);
			cout << RIGHT_CROSS;
		}
	}
	for (int i = 0; i < height; i++)
	{
		GotoXY(x, y + (row - 1) * (height + 1) + 1 + i);
		cout << V_LINE;
		DrawTableLine(col, SPACE, V_LINE, width);
		cout << V_LINE;
	}

	GotoXY(x, y + (row - 1) * (height + 1) + 1 + height);
	cout << BOTTOM_LEFT;
	DrawTableLine(col, H_LINE, BOTTOM_CROSS, width);
	cout << BOTTOM_RIGHT;
}
