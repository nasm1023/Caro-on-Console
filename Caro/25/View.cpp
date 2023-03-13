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
	GotoXY(dx, dy);
	cout << BOX_TOP_LEFT;
	for (int i = 1; i < w - 1; i++)
	{
		cout << BOX_H_LINE;
		Sleep(5);
	}

	cout << BOX_TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(dx, i + dy);
		cout << BOX_V_LINE;
		for (int j = 1; j < w - 1; j++)
			cout << SPACE;
		cout << BOX_V_LINE;
		Sleep(5);
	}

	GotoXY(dx, h + dy - 1);
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
	unsigned char logo[] = {32, 32, 220, 219, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219, 219, 32, 32, 32, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219, 219, 219, 32, 32,
							219, 219, 32, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 32, 219, 219,
							219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 32, 219, 219,
							219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 219, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219, 219, 32, 32, 32, 219, 219, 32, 32, 32, 32, 32, 219, 219,
							219, 219, 32, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 32, 219, 219,
							32, 32, 219, 219, 219, 219, 219, 32, 32, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219, 32, 32, 32, 219, 219, 219, 219, 219, 32, 32};
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
	unsigned char Note[] = { 179, 32, 80, 114, 111, 106, 101, 99, 116, 32, 98, 121, 32, 71, 114, 111, 117, 112, 32, 49, 51, 32, 45, 32, 50, 50, 67, 84, 84, 52, 32, 72, 67, 77, 85, 83, 32, 179};
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

void DrawBoxMini(int w, int h, int dx, int dy, int color)
{
	TextColor(color);
	GotoXY(dx, dy);
	cout << TOP_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << H_LINE;
	cout << TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(dx, i + dy);
		cout << V_LINE;
		for (int j = 1; j < w - 1; j++)
			cout << SPACE;
		cout << V_LINE;
	}

	GotoXY(dx, h + dy - 1);
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