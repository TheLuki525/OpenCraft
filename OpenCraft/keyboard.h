#pragma once
class Keyboard
{
	BYTE key[256];
	bool key_state[2][256];
	char short_released[256];
	char short_pressed[256];
	bool phase{ false };
	HWND HgameWindow;
public:
	Keyboard(HWND);
	unsigned int update();
	bool getKeyState(char);
	bool isShortReleased(char);
	bool isShortPressed(char);
	bool Released_Pressed(char);
};