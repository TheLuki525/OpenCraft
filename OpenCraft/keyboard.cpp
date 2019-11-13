#include "stdafx.h"
#include "keyboard.h"
#include "game.h"

Keyboard::Keyboard(HWND h)
{
	HgameWindow = h;
}

unsigned int Keyboard::update()
{
	phase = !phase;
	GetKeyState(0);
	if (!GetKeyboardState(key))
		return GetLastError();
	for (int i = 0; i < 256; i++)
	{
		key_state[phase][i] = key[i] >> 7;
		if (key_state[phase][i] != key_state[!phase][i])//key state change
		{
			if (key_state[phase][i])//pressed now
				short_pressed[i] = 15;
			else//released now
				short_released[i] = 15;
		}
		else//no kaystate change
		{
			if (short_pressed[i] && key_state[phase][i])
				short_pressed[i]--;
			if (short_released[i] && !key_state[phase][i])
				short_released[i]--;
		}
	}
	return 0;
}

bool Keyboard::getKeyState(char c)
{
	if (GetForegroundWindow() == HgameWindow)
		return key_state[phase][c];
	return false;
}

bool Keyboard::isShortReleased(char key)
{
	if (GetForegroundWindow() == HgameWindow)
		return short_released[key];
	return false;
}

bool Keyboard::isShortPressed(char key)
{
	if (GetForegroundWindow() == HgameWindow)
		return short_pressed[key];
	return false;
}

bool Keyboard::Released_Pressed(char key)
{
	return key_state[phase][key] == true && key_state[phase][key] != key_state[!phase][key];
}
