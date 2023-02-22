#include "View.h"
#include "Data.h"
#include "Control.h"
#include <conio.h>
using namespace std;

int main() {
	SetConsoleColor();
	TextColor(BLUE);
	/*GotoXY(5, 5);
	cout << TOP_LEFT << H_LINE << H_LINE << H_LINE << TOP_RIGHT;
	GotoXY(5, 6);
	cout << V_LINE << SPACE << SPACE << SPACE << V_LINE;
	GotoXY(5, 7);
	cout << BOTTOM_LEFT << H_LINE << H_LINE << H_LINE << BOTTOM_RIGHT;

	GotoXY(7, 6);
	cout << "X";

	GotoXY(10, 5);
	cout << TOP_LEFT << H_LINE << H_LINE << H_LINE << TOP_RIGHT;
	GotoXY(10, 6);
	cout << V_LINE << SPACE << SPACE << SPACE << V_LINE;
	GotoXY(10, 7);
	cout << BOTTOM_LEFT << H_LINE << H_LINE << H_LINE << BOTTOM_RIGHT;*/
	DrawBoard(10, 10, 3, 1, 2, 1);
	Menu();
	return 0;
}