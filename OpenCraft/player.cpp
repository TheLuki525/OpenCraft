#include "stdafx.h"
#include "player.h"
#include "myfunctions.h"

#define TURN_SPEED 6.0f

Player::Player()
{
	phase = 0;
	flashLight = false;
	char filename[32] = "head.bmp";
	texHead = LoadTexture(filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	
}

void Player::walk(bool FWD, bool BWD, bool LFT, bool RGT, bool RUN)
{
	if (FWD && BWD)
		FWD = BWD = false;

	if (LFT && RGT)
		LFT = RGT = false;

	RUN &= FWD;
	vec3 dir;
	if (FWD)
	{
		if (LFT)//FORWARD + LEFT
		{
			float global_head_angle_RAD = (ang.y + head_ang.y)*TO_RAD;
			if (head_ang.y > -max_neck_angle)
			{
				ang.y += TURN_SPEED;
				head_ang.y -= TURN_SPEED;
			}
			vec3 tmp(sinf(global_head_angle_RAD + 45.0f*TO_RAD), -sinf(ang.to_RAD().x), cosf(ang.to_RAD().x)*cosf(global_head_angle_RAD + 45.0f*TO_RAD));
			dir = tmp;
		}
		else if (RGT)//FORWARD + RIGHT
		{
			float global_head_angle_RAD = (ang.y + head_ang.y)*TO_RAD;
			if (head_ang.y < max_neck_angle)
			{
				ang.y -= TURN_SPEED;
				head_ang.y += TURN_SPEED;
			}
			vec3 tmp(sinf(global_head_angle_RAD - 45.0f*TO_RAD), -sinf(ang.to_RAD().x), cosf(ang.to_RAD().x)*cosf(global_head_angle_RAD - 45.0f*TO_RAD));
			dir = tmp;
		}
		else//FORWARD only
		{
			if (head_ang.y > TURN_SPEED)
			{
				ang.y += TURN_SPEED;
				head_ang.y -= TURN_SPEED;
			}
			else if (head_ang.y < -TURN_SPEED)
			{
				ang.y -= TURN_SPEED;
				head_ang.y += TURN_SPEED;
			}
			else
			{
				ang.y += head_ang.y;
				head_ang.y = 0;
			}
			vec3 tmp(sinf(ang.to_RAD().y), -sinf(ang.to_RAD().x), cosf(ang.to_RAD().x)*cosf(ang.to_RAD().y));
			dir = tmp;
		}
	}
	else if (BWD)
	{
		if (LFT)//BACKWARD + LEFT
		{
			float global_head_angle_RAD = (ang.y + head_ang.y)*TO_RAD;
			if (head_ang.y < max_neck_angle)
			{
				ang.y -= TURN_SPEED;
				head_ang.y += TURN_SPEED;
			}
			vec3 tmp(sinf(global_head_angle_RAD + 135.0f*TO_RAD), -sinf(ang.to_RAD().x), cosf(ang.to_RAD().x)*cosf(global_head_angle_RAD + 135.0f*TO_RAD));
			dir = tmp;
		}
		else if (RGT)//BACKWARD + RIGHT
		{
			float global_head_angle_RAD = (ang.y + head_ang.y)*TO_RAD;
			if (head_ang.y > -max_neck_angle)
			{
				ang.y += TURN_SPEED;
				head_ang.y -= TURN_SPEED;
			}
			vec3 tmp(sinf(global_head_angle_RAD - 135.0f*TO_RAD), -sinf(ang.to_RAD().x), cosf(ang.to_RAD().x)*cosf(global_head_angle_RAD - 135.0f*TO_RAD));
			dir = tmp;
		}
		else//BACKWARD only
		{
			if (head_ang.y > TURN_SPEED)
			{
				ang.y += TURN_SPEED;
				head_ang.y -= TURN_SPEED;
			}
			else if (head_ang.y < -TURN_SPEED)
			{
				ang.y -= TURN_SPEED;
				head_ang.y += TURN_SPEED;
			}
			else
			{
				ang.y += head_ang.y;
				head_ang.y = 0;
			}
			vec3 tmp(-sinf(ang.to_RAD().y), sinf(ang.to_RAD().x), -cosf(ang.to_RAD().x)*cosf(ang.to_RAD().y));
			dir = tmp;
		}
	}
	else
	{
		if (LFT)//LEFT only
		{
			float global_head_angle_RAD = (ang.y + head_ang.y)*TO_RAD;
			if (head_ang.y > -max_neck_angle)
			{
				ang.y += TURN_SPEED;
				head_ang.y -= TURN_SPEED;
			}
			vec3 tmp(sinf(global_head_angle_RAD + 90.0f*TO_RAD), -sinf(ang.to_RAD().x), cosf(ang.to_RAD().x)*cosf(global_head_angle_RAD + 90.0f*TO_RAD));
			dir = tmp;
		}
		else if (RGT)//RIGHT only
		{
			float global_head_angle_RAD = (ang.y + head_ang.y)*TO_RAD;
			if (head_ang.y < max_neck_angle)
			{
				ang.y -= TURN_SPEED;
				head_ang.y += TURN_SPEED;
			}
			vec3 tmp(sinf(global_head_angle_RAD - 90.0f*TO_RAD), -sinf(ang.to_RAD().x), cosf(ang.to_RAD().x)*cosf(global_head_angle_RAD - 90.0f*TO_RAD));
			dir = tmp;
		}
	}


	if (dir.length())
	{
		if (on_ground)
		{
			dir.normalize();
			dir *= 0.05f;
			if (RUN)
				dir *= 4.0f;
			speed = dir;
		}
		else
		{
			dir.normalize();
			dir *= 0.007f;
			dir.y = 0.0f;
			speed += dir;
			speed.x *= 0.95f;
			speed.z *= 0.95f;
		}

		if (!RUN && fabs(phase) > 27)
		{
			if (phase < 0)
				phase = -24.0f;
			else
				phase = 24.0f;
		}

		if (fabs(phase) > 25 + (RUN != 0) * 40)
			phase_dir = !phase_dir;

		if (phase_dir)
			phase += 3 + (RUN != 0) * 6;
		else
			phase -= 3 + (RUN != 0) * 6;
	}
	else
	{
		if (phase > 3)
			phase -= 3;
		else if (phase < -3)
			phase += 3;
		else
			phase = 0;

		if (on_ground)
			speed *= 0.0f;
	}
}

void Player::draw(bool cam_mode)
{
	//if (180.0f - abs(abs(head_ang.y - ang.y) - 180.0f) > max_neck_angle)//character turn, when the max neck angle reached
	if (ang.y >= 360.0f)//camera + head angle normalization
		ang.y -= 360.0f;
	else if (ang.y <= -360.0f)
		ang.y += 360.0f;

	if (ang.x >= 360.0f)//head angle normalization
		ang.x -= 360.0f;
	else if (ang.x <= -360.0f)
		ang.x += 360.0f;


	if (head_ang.y > max_neck_angle)
	{
		ang.y += head_ang.y - max_neck_angle;
		head_ang.y = max_neck_angle;
	}
	else if (head_ang.y < -max_neck_angle)
	{
		ang.y += head_ang.y + max_neck_angle;
		head_ang.y = -max_neck_angle;
	}


	if (flashLight)
	{
		//spotlight
		glEnable(GL_LIGHT1);
		float l1_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l1_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l1_pos[] = { pos.x, pos.y + 2.4f, pos.z, 1.0f };
		glLightfv(GL_LIGHT1, GL_AMBIENT, l1_amb);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_dif);
		glLightfv(GL_LIGHT1, GL_SPECULAR, l1_spe);
		glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
		float const_att = 0.0f;
		glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, &const_att);
		float lin_att = 0.1f;
		glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, &lin_att);
		float quad_att = 0.02f;
		glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, &quad_att);
		float global_head_angle_y = head_ang.y + ang.y;
		float global_head_angle_x = -head_ang.x;
		vec3 dir = two_angles_to_vec3(global_head_angle_x, global_head_angle_y);
		float flDir[] = { dir.x, dir.y, dir.z };
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, flDir);
		float exp = 0.0f;
		glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, &exp);
		float cutoff = 15.0f;
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, &cutoff);
	}
	else
		glDisable(GL_LIGHT1);

	if (!cam_mode)//in 1st person camera the character is not drawed
		return;
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(ang.x, 1.0f, 0.0f, 0.0f);
		glRotatef(ang.y, 0.0f, 1.0f, 0.0f);
		glRotatef(ang.z, 0.0f, 0.0f, 1.0f);
		glScalef(0.0357f*PLAYER_EYE_HEIGHT, 0.0357f*PLAYER_EYE_HEIGHT, 0.0357f*PLAYER_EYE_HEIGHT);

		float mR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float mG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		float mB[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		float mY[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

		glPushMatrix();//Noga_L
		{
			glTranslatef(2.0f, 12.0f, 0.0f);
			glRotatef(phase, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -6.0f, 0.0f);
			glScalef(4.0f, 12.0f, 4.0f);
			//glColor3f(0.0f, 1.0f, 0.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mB);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mB);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mB);
			glutSolidCube(1.0f);
		}
		glPopMatrix();
		glPushMatrix();//Noga_P
		{
			glTranslatef(-2.0f, 12.0f, 0.0f);
			glRotatef(-phase, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -6.0f, 0.0f);
			glScalef(4.0f, 12.0f, 4.0f);
			//glColor3f(0.0f, 1.0f, 0.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mG);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mG);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mG);
			glutSolidCube(1.0f);
		}
		glPopMatrix();
		glPushMatrix();//Tulow
		{
			glTranslatef(0.0f, 18.0f, 0.0f);
			glScalef(8.0f, 12.0f, 4.0f);
			//glColor3f(1.0f, 0.0f, 0.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mR);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mR);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mR);
			glutSolidCube(1.0f);
		}
		glPopMatrix();
		glPushMatrix();//Reka_L
		{
			glTranslatef(6.0f, 24.0f, 0.0f);
			glRotatef(2.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(-phase, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -6.0f, 0.0f);
			glScalef(4.0f, 12.0f, 4.0f);
			//glColor3f(0.0f, 0.0f, 1.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mB);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mB);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mB);
			glutSolidCube(1.0f);
		}
		glPopMatrix();
		glPushMatrix();//Reka_P
		{
			glTranslatef(-6.0f, 24.0f, 0.0f);
			glRotatef(-2.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(phase, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -6.0f, 0.0f);
			glScalef(4.0f, 12.0f, 4.0f);
			//glColor3f(0.0f, 1.0f, 0.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mG);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mG);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mG);
			glutSolidCube(1.0f);
		}
		glPopMatrix();
		glPushMatrix();//Glowa
		{
			glTranslatef(0.0f, 24.0f, 0.0f);
			glRotatef(head_ang.x, 1.0f, 0.0f, 0.0f);
			glRotatef(head_ang.y, 0.0f, 1.0f, 0.0f);
			glRotatef(head_ang.z, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, 4.0f, 0.0f);
			glScalef(8.0f, 8.0f, 8.0f);
			//glColor3f(1.0f, 1.0f, 0.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mY);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mY);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mY);
			glutSolidCube(1.0f);
			/*
			
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			float m_amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
			float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
				glBindTexture(GL_TEXTURE_2D, texHead);

				glPushMatrix();
					glScalef(.5f, .5f, .5f);
					glTranslatef(4.5f, 2.0f, 3.0f);
					glRotatef(3*phase, 0.0f, 1.0f, 0.0f);
		
					glBegin(GL_QUADS);
			
						glTexCoord2f( 0.0f,  1.0f);
						glNormal3f( 0.0f,  0.0f,  1.0f);
						glVertex3f(-1.0f,  1.0f,  0.0f);
			
						glTexCoord2f( 0.0f,  0.0f);
						glNormal3f( 0.0f,  0.0f,  1.0f);
						glVertex3f(-1.0f, -1.0f,  0.0f);
			
						glTexCoord2f( 1.0f,  0.0f);
						glNormal3f( 0.0f,  0.0f,  1.0f);
						glVertex3f( 1.0f, -1.0f,  0.0f);
			
						glTexCoord2f( 1.0f,  1.0f);
						glNormal3f( 0.0f,  0.0f,  1.0f);
						glVertex3f( 1.0f,  1.0f,  0.0f);
			
			
						glTexCoord2f( 0.0f,  0.0f);
						glNormal3f( 0.0f,  0.0f, -1.0f);
						glVertex3f(-1.0f, -1.0f,  0.0f);
			
						glTexCoord2f( 0.0f,  1.0f);
						glNormal3f( 0.0f,  0.0f, -1.0f);
						glVertex3f(-1.0f,  1.0f,  0.0f);
			
						glTexCoord2f( 1.0f,  1.0f);
						glNormal3f( 0.0f,  0.0f, -1.0f);
						glVertex3f( 1.0f,  1.0f,  0.0f);
			
						glTexCoord2f( 1.0f,  0.0f);
						glNormal3f( 0.0f,  0.0f, -1.0f);
						glVertex3f( 1.0f, -1.0f,  0.0f);

					glEnd();

				glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			*/
			
		}
		glPopMatrix();
	}
	glPopMatrix();
}
