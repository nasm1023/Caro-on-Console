#include "Data.h"
#include "Control.h"
#include "View.h"

int main() {
	FixConsoleWindow();
	SetConsoleBlank();
	//PlaySound(BGM, NULL, SND_FILENAME | SND_ASYNC);
	//PlaySound(CLICK_SFX, NULL, SND_FILENAME | SND_ASYNC);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	// Get the current console attributes so we can restore them later
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	// Set the text color to green
	//SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
	TextColor(BLUE ^ 240 | BACKGROUND_RED);

	// Output some text with the green text color
	cout << "Hello, world!\n";
	return 0;
	MainMenu();
	//DrawBoard(1, 1, 5, 2, CYAN);

	GotoXY(0, 28);
	return 0;
}