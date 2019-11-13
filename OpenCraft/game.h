#pragma once
#include "stdafx.h"
#include "camera.h"
#include "player.h"
#include "keyboard.h"
#include "Map.h"

class Game
{
	unsigned int window_width;
	unsigned int window_height;
	unsigned int best;
	int time;
	int current_time;
	int pauseTime;
	bool pause;
	bool nickname_rdy;
	int runKeyPressed;
	bool run_state;
	Camera cam;
	Player ch1;
	Keyboard* kb;
	HWND HgameWindow;
	Map map;
	std::string nickname;
	void OnRender();
	void OnReshape(int width, int height);
	void OnTimer(int id);
	void CursorPosUpdate(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void setHgameWindow(HWND);
	void renderBitmapString(float x, float y, std::string text);
public:
	Game();
	~Game();
	friend void OnRenderCallback();
	friend void OnReshapeCallback(int width, int height);
	friend void OnTimerCallback(int id);
	friend void CursorPosUpdateCallback(int x, int y);
	friend void SetupGLUT(int &argc, char** argv);
	friend void MouseCallback(int button, int state, int x, int y);
};

