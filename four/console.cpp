#include "stdafx.h"

#include "console.h"


// Define the static member variables.
HANDLE Console::hScreenBuffer;
CONSOLE_SCREEN_BUFFER_INFO Console::screenInfo;

void Console::init(void)
{
	hScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hScreenBuffer == INVALID_HANDLE_VALUE) {
		error_exit("Can't get screen handle");
	}
	GetConsoleScreenBufferInfo(hScreenBuffer, &screenInfo);
	clear();
}

void Console::deinit(void)
{
	// restore l'�t� initial de la Console (couleur,...)
	SetConsoleTextAttribute(hScreenBuffer, screenInfo.wAttributes);

}

void Console::error_exit(const std::string& s) {
	std::cerr << s;

	system("pause");
	ExitProcess(0);
}

void Console::set_title(const std::string& s) {
	SetConsoleTitle(s.c_str());
}

void Console::set_cursor_color(color c) {
	switch (c) {
	case default_color:
		SetConsoleTextAttribute(hScreenBuffer, 0);
		break;
	case red:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED);
		break;
	case yellow:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case green:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_GREEN);
		break;
	case cyan:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case blue:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_BLUE);
		break;
	case magenta:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case white:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:
		error_exit("Unknown color in set_cursor_color");
	}
}

void Console::set_cursor_position(const COORD& p) {
	SetConsoleCursorPosition(hScreenBuffer, p);
}

void Console::clear() {
	system("CLS");
}

void Console::set_dimensions(unsigned int w, unsigned int h) {
	COORD cSize = { w,h };
	int result = SetConsoleScreenBufferSize(hScreenBuffer, cSize);
	if (result == 0) {
		error_exit("SetConsoleScreenBufferSize");
	}
}