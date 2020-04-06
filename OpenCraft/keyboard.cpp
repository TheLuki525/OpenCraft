#include "stdafx.h"
#include "keyboard.h"
#include "game.h"

Keyboard::Keyboard(HWND h)
{
	HgameWindow = h;
	current_key_state = new bool[256]{ false };
	old_key_state = new bool[256]{ false };
}

Keyboard::~Keyboard()
{
	delete[] current_key_state;
	delete[] old_key_state;
}

unsigned int Keyboard::update()
{
	GetKeyState(0);
	if (!GetKeyboardState(key))
		return GetLastError();
	std::swap(old_key_state, current_key_state);
	for (int i = 0; i < 256; i++)
	{
		current_key_state[i] = key[i] >> 7;
		if (current_key_state[i] != old_key_state[i])//key state change
		{
			if (current_key_state[i])//pressed now
				short_pressed[i] = 15;
			else//released now
				short_released[i] = 15;
		}
		else//no kaystate change
		{
			if (short_pressed[i] && current_key_state[i])
				short_pressed[i]--;
			if (short_released[i] && !current_key_state[i])
				short_released[i]--;
		}
	}
	return 0;
}

bool Keyboard::getKeyState(char c)
{
	if (GetForegroundWindow() == HgameWindow)
		return current_key_state[c];
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

bool Keyboard::justPressed(char key)
{
	return current_key_state[key] == true && current_key_state[key] != old_key_state[key];
}
