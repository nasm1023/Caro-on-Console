#include "View.h"
#include "Data.h"
#include "Control.h"
using namespace std;

int main() {
	SetConsole(WIDTH, HEIGHT);
	GotoXY(WIDTH / 2, HEIGHT / 2);
	cout << "Hello :D";
	Menu();
	return 0;
}