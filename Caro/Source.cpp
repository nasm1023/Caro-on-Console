#include "Data.h"
#include "Control.h"
#include "View.h"

int main() {
	FixConsoleWindow();
	SetConsoleBlank();
	//MainMenu();
	DrawBoard(B_SIZE, B_SIZE, 5, 2, CYAN);

	GotoXY(0, 28);
	return 0;
}