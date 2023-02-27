#include "Data.h"
#include "Control.h"
#include "View.h"

int main() {
	FixConsoleWindow();
	SetConsoleBlank();
	//(BGM, NULL, SND_ASYNC);
	MainMenu();
	//DrawBoard(1, 1, 5, 2, CYAN);

	GotoXY(0, 28);
	return 0;
}