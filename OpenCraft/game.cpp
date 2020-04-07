#include "stdafx.h"
#include "game.h"
#include "vec3.h"
#include "myfunctions.h"

Game::Game()
{
	window_width = 640;
	window_height = 360;
	HgameWindow = nullptr;
	kb = nullptr;
	pause = true;
	nickname_rdy = false;
	ch1.pos.x = 0.0f;
	ch1.pos.y = 60.0f;
	ch1.pos.z = 0.0f;
	time = -1;
	srand(123);
	runKeyPressed = 0;
	run_state = false;
}

Game::~Game()
{
	delete kb;
}

void Game::OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
#pragma region RenderingPauseMenu
	if (pause)//rendering pause menu
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		{
			glLoadIdentity();
			gluOrtho2D(100, 0, 100, 0);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			{
				glLoadIdentity();
				glDisable(GL_LIGHTING);
				glDisable(GL_CULL_FACE);
				glColor3f(0.7f, 1.0f, 0.0f);
				std::string text = "\"P\" Enables/disables this pause menu";
				renderBitmapString(95.0f, 10.0f, text);
				text = "\"L\" Enables/disables player's flashlight";
				renderBitmapString(95.0f, 17.0f, text);
				glColor3f(0.7f, 0.0f, 0.7f);
				text = "The point of this game is getting as high as you can";
				renderBitmapString(95.0f, 27.0f, text);
				glColor3f(0.0f, 1.0f, 0.0f);
				text = "Enter your nickname:";
				renderBitmapString(95.0f, 45.0f, text);
				if(nickname_rdy)
					glColor3f(0.0f, 1.0f, 0.0f);
				else
					glColor3f(1.0f, 1.0f, 0.0f);
				text = nickname;
				if (!nickname_rdy && GetTickCount() % 1000 < 500)//flashing cursor
					text += 'I';
				renderBitmapString(95.0f, 55.0f, text);
				glColor3f(0.0f, 1.0f, 0.0f);
				text = "And then hit Return";
				renderBitmapString(95.0f, 65.0f, text);
				glColor3f(1.0f, 0.0f, 0.0f);
				text = "TOP SCORES: ";
				renderBitmapString(50.0f, 40.0f, text);
				std::fstream file;
				file.open("top.txt", std::ios::in);
				if (file.good())
				{
					float offset = 50.0f;
					while (!file.eof())
					{
						int score;
						file >> score;
						std::string nick;
						file >> nick;
						renderBitmapString(45.0f, offset, std::to_string(score));
						renderBitmapString(40.0f, offset, nick);
						offset += 5;
					}
				}
				else
				{
					text = "No high scores yet.";
					renderBitmapString(45.0f, 50.0, text);
				}
				file.close();
				//glRasterPos3f(50, 50, 1.0f);
				//glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
				//glScalef(0.05, 0.05, 0.05);
				//glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"The game over!");
				glEnable(GL_LIGHTING);
				glEnable(GL_CULL_FACE);
				glMatrixMode(GL_PROJECTION);
			}
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
		glPopMatrix();

		glFlush();
		glutSwapBuffers();
		glutPostRedisplay();
		return;
	}
#pragma endregion

#pragma region RenderingGameWorld
	float global_head_angle_y = ch1.head_ang.y + ch1.ang.y;
	float global_head_angle_x = -ch1.head_ang.x;

	cam.set(two_angles_to_vec3(global_head_angle_x, global_head_angle_y), ch1.pos);
	//Drawing the map
	glPushMatrix();
	{
		glTranslatef(0.5f, 0.5f, 0.5f);
		map.draw();
	}
	glPopMatrix();
	
	//sun - directional light
	glEnable(GL_LIGHT0);
	float l0_amb[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_pos[] = { 100.0f*cosf(GetTickCount()*0.001f), 20.0f, 100.0f*sinf(GetTickCount()*0.001f), 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

	if (!kb)
		return;
	ch1.flashLight ^= kb->justPressed('L');//I'm so proud of myself xD
	ch1.draw(cam.mode);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glLoadIdentity();
		gluOrtho2D(100, 0, 100, 0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glLoadIdentity();
			glDisable(GL_LIGHTING);
			glDisable(GL_CULL_FACE);
			float r, g;
			current_time >= TOTAL_TIME / 2 ? g = 1.0f : r = 1.0f;
			current_time >= TOTAL_TIME / 2 ? r = 2.0f - current_time / (TOTAL_TIME / 2.0f) : g = current_time / (TOTAL_TIME / 2.0f);
			glColor3f(r, g, 0.0f);
			std::string text = "TIME REMAINING: " + std::to_string(current_time);
			renderBitmapString(97.0f, 5.0f, text);
			text = "CURRENT HEIGHT: " + std::to_string(static_cast<int>(ch1.pos.y));
			renderBitmapString(62.0f, 5.0f, text);
			text = "BEST HEIGHT: " + std::to_string(best);
			renderBitmapString(27.0f, 5.0f, text);
			glEnable(GL_LIGHTING);
			glEnable(GL_CULL_FACE);
			glMatrixMode(GL_PROJECTION);
		}
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	glPopMatrix();

#pragma endregion
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Game::OnReshape(int width, int height)
{
	window_width = width;
	window_height = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, static_cast<float>(width) / height, 0.01f, 100.0f);
}

void Game::OnTimer(int id)
{
	if (!kb)
		return;

	kb->update();

#pragma region InputAndPauseOperations

	if (kb->getKeyState(VK_ESCAPE))//leaving the game
		glutLeaveMainLoop();
	bool pause_old = pause;

	if (nickname_rdy)//can't leave pause menu without nickname
		pause ^= kb->justPressed('P');

	if (pause && !pause_old)//pause menu just enabled
		pauseTime = GetTickCount();

	if (pause)
	{
		if(!nickname_rdy)
			for (char i = 'A'; i <= 'Z'; i++)//signs from A-Z
				if (kb->justPressed(i))
					nickname += i;
		if (!nickname_rdy)//numbers from 0-9
			for (char i = '0'; i <= '9'; i++)
				if (kb->justPressed(i))
					nickname += i;
		if (kb->justPressed(VK_BACK) && nickname.length() > 0)//erasing last char with backspace
			nickname.resize(nickname.length()-1);
		if (kb->getKeyState(VK_RETURN) && nickname.length() > 0)//nickname ready after return
			nickname_rdy = true;
		if (nickname.length() > 15)//nickname max length
			nickname_rdy = true;

		return;
	}

	if (time == -1)//game just started
	{
		time = GetTickCount();
		ch1.head_ang.x = 0.0f;
		ch1.head_ang.y = 0.0f;

	}

	if (pauseTime > 0)//adding time spent in pause menu to player's time
		pauseTime = GetTickCount() - pauseTime;
	time += pauseTime;
	pauseTime = 0;

	current_time = (time + TOTAL_TIME*1000 - GetTickCount()) / 1000;//calculating current time left

#pragma endregion

#pragma region EndOfRound

	std::string tmp;
	if (current_time <= 0 && current_time != -1)//time's up!
	{
		std::fstream file;
		file.open("top.txt", std::ios::in | std::ios::out);
		if (file.good())
		{
			unsigned int score[3];
			std::string nick[3];
			for (int i = 0; i < 3; i++)
				file >> score[i] >> nick[i];
			if (best > score[0])
			{
				score[2] = score[1];
				score[1] = score[0];
				score[0] = best;
				nick[2] = nick[1];
				nick[1] = nick[0];
				nick[0] = nickname;
			}
			else if (best > score[1])
			{
				score[2] = score[1];
				score[1] = best;
				nick[2] = nick[1];
				nick[1] = nickname;
			}
			else if (best > score[2])
			{
				score[2] = best;
				nick[2] = nickname;
			}
			for (int i = 0; i < 3; i++)
				tmp += std::to_string(score[i]) + ' ' + nick[i] + '\n';
			tmp[tmp.length() - 1] = 0;
		}
		file.close();
		file.open("top.txt", std::ios::out);
		if (file.good())
			file << tmp;
		file.close();
		pause = true;
		nickname_rdy = false;
		ch1.pos.x = 0.0f;
		ch1.pos.y = 60.0f;
		ch1.pos.z = 0.0f;
		best = 0;
		time = -1;
	}
#pragma endregion

#pragma region WalkingGravityJumping

	if (kb->justPressed('W') && runKeyPressed <= 0)
		runKeyPressed = 30;
	if (runKeyPressed > 0 && runKeyPressed < 30 && kb->justPressed('W'))
		run_state = true;
	if (run_state && !kb->getKeyState('W'))
		run_state = false;
	if(runKeyPressed > 0)
		runKeyPressed--;
	ch1.walk(kb->getKeyState('W'), kb->getKeyState('S'), kb->getKeyState('A'), kb->getKeyState('D'), run_state);

	
	if (ch1.on_ground)//gravity and jumping
	{
		if (kb->getKeyState(' '))
			ch1.speed.y += 0.25f;
	}
	else
		ch1.speed.y -= 0.02f;
	

#pragma endregion

#pragma region Collisions
	if (ch1.pos.y <= 0.0005f)//protection against falling under the map
	{
		ch1.on_ground = true;
		if (ch1.speed.y < 0)
			ch1.speed.y = 0.0f;
		ch1.pos.y = 0.0f;
	}
	else
		ch1.on_ground = false;
	if (map.getBlock(ch1.pos.x, ch1.pos.y - 0.005f, ch1.pos.z))//foot collision
	{
		ch1.on_ground = true;
		if (ch1.speed.y < 0)
			ch1.speed.y = 0;
		ch1.pos.y = ceilf(ch1.pos.y);
	}
	if (ch1.speed.y > 0.0f && map.getBlock(ch1.pos.x, ch1.pos.y + 1.9f, ch1.pos.z))//head collision
	{
		ch1.speed.y = 0.0f;
	}
	if (map.getBlock(ch1.pos.x - 0.3f, ch1.pos.y + 1.1f, ch1.pos.z) || map.getBlock(ch1.pos.x - 0.3f, ch1.pos.y + 0.1f, ch1.pos.z))//X-axis(-) collision
	{
		if (ch1.speed.x < 0.0f)
			ch1.speed.x = 0;
	}
	if (map.getBlock(ch1.pos.x + 0.3f, ch1.pos.y + 1.1f, ch1.pos.z) || map.getBlock(ch1.pos.x + 0.3f, ch1.pos.y + 0.1f, ch1.pos.z))//X-axis(+) collision
	{
		if (ch1.speed.x > 0.0f)
			ch1.speed.x = 0;
	}
	if (map.getBlock(ch1.pos.x, ch1.pos.y + 1.0f, ch1.pos.z - 0.3f) || map.getBlock(ch1.pos.x, ch1.pos.y, ch1.pos.z - 0.3f))//Z-axis(-) collision
	{
		if (ch1.speed.z < 0.0f)
			ch1.speed.z = 0;
	}
	if (map.getBlock(ch1.pos.x, ch1.pos.y + 1.0f, ch1.pos.z + 0.3f) || map.getBlock(ch1.pos.x, ch1.pos.y, ch1.pos.z + 0.3f))//Z-axis(+) collision
	{
		if (ch1.speed.z > 0.0f)
			ch1.speed.z = 0;
	}
#pragma endregion

#pragma region BestScoreCalculation
	if (ch1.on_ground)
		if (ch1.pos.y > best)
			best = static_cast<int>(ch1.pos.y);
#pragma endregion

	ch1.pos += ch1.speed;

}

void Game::CursorPosUpdate(int x, int y)
{
	if (GetForegroundWindow() != HgameWindow)//if the game window isin't active, cursor operations are cancelled 
		return;
	if (x != window_width >> 1 || y != window_height >> 1)//if cursor is in the middle of game window, it will not be warped
	{
		ch1.head_ang.y -= (static_cast<float>(x) - (window_width >> 1))*0.1f;
		ch1.head_ang.x += (static_cast<float>(y) - (window_height >> 1))*0.1f;
		glutWarpPointer(window_width >> 1, window_height >> 1);
		if (ch1.head_ang.x > 89.0f)
			ch1.head_ang.x = 89.0f;
		else if (ch1.head_ang.x < -89.0f)
			ch1.head_ang.x = -89.0f;
	}
}

void Game::Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
		return;
	if (button == 3) //wheel-up event
		cam.expected_dist++;
	else if (button == 4)//wheel-down event
		cam.expected_dist--;
}

void Game::setHgameWindow(HWND h)
{
	HgameWindow = h;
	kb = new Keyboard(h);
}

void Game::renderBitmapString(float x, float y, std::string text)
{
	glRasterPos3f(x, y, 1.0f);
	for (unsigned int i = 0; i < text.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);//GLUT_BITMAP_TIMES_ROMAN_24
}