#include "Data.h"
#include "Control.h"
#include "View.h"
#include "Model.h"

int main() {
	FixConsoleWindow();
	MainMenu();
	_getch();
	StartGame();
	return 0;
}