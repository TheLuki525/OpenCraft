#pragma once
class Keyboard
{
	BYTE key[256];
	bool *current_key_state;
	bool *old_key_state;
	char short_released[256];
	char short_pressed[256];
	HWND HgameWindow;
public:
	Keyboard(HWND);
	~Keyboard();
	unsigned int update();
	bool getKeyState(char);
	bool isShortReleased(char);
	bool isShortPressed(char);
	bool justPressed(char);
};