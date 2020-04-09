#include "stdafx.h"
#include "vec3.h"

void vec3::operator+=(vec3 c)
{
	x += c.x;
	y += c.y;
	z += c.z;
}

void vec3::operator-=(vec3 c)
{
	x -= c.x;
	y -= c.y;
	z -= c.z;
}

void vec3::operator*=(vec3 c)
{
	x *= c.x;
	y *= c.y;
	z *= c.z;
}

void vec3::operator/=(vec3 c)
{
	x /= c.x;
	y /= c.y;
	z /= c.z;
}

void vec3::operator+=(int c)
{
	x += c;
	y += c;
	z += c;
}

void vec3::operator-=(int c)
{
	x -= c;
	y -= c;
	z -= c;
}

void vec3::operator*=(int c)
{
	x *= c;
	y *= c;
	z *= c;
}

void vec3::operator/=(int c)
{
	x /= c;
	y /= c;
	z /= c;
}

void vec3::operator+=(float c)
{
	x += c;
	y += c;
	z += c;
}

void vec3::operator-=(float c)
{
	x -= c;
	y -= c;
	z -= c;
}

void vec3::operator*=(float c)
{
	x *= c;
	y *= c;
	z *= c;
}

void vec3::operator/=(float c)
{
	x /= c;
	y /= c;
	z /= c;
}

vec3 vec3::to_RAD()
{
	vec3 ret(x, y, z);
	ret *= TO_RAD;
	return ret;
}

vec3 two_angles_to_vec3(float angx, float angy)
{
	angx *= TO_RAD;
	angy *= TO_RAD;
	return vec3(sinf(angy) * cosf(angx), sinf(angx), cosf(angy) * cosf(angx));
}

float vec3::length()
{
	return sqrtf(x * x + y * y + z * z);
}

void vec3::normalize()
{
	float len = this->length();
	if (len)
		(*this) /= len;
}

vec3::vec3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

vec3::vec3(float xx = 0, float yy = 0, float zz = 0)
{
	x = xx;
	y = yy;
	z = zz;
}

vec3 operator+(vec3 v, int c)
{
	v.x += c;
	v.y += c;
	v.z += c;
	return v;
}

vec3 operator-(vec3 v, int c)
{
	v.x -= c;
	v.y -= c;
	v.z -= c;
	return v;
}

vec3 operator*(vec3 v, int c)
{
	v.x *= c;
	v.y *= c;
	v.z *= c;
	return v;
}

vec3 operator/(vec3 v, int c)
{
	v.x /= c;
	v.y /= c;
	v.z /= c;
	return v;
}

vec3 operator+(vec3 v, float c)
{
	v.x += c;
	v.y += c;
	v.z += c;
	return v;
}

vec3 operator-(vec3 v, float c)
{
	v.x -= c;
	v.y -= c;
	v.z -= c;
	return v;
}

vec3 operator*(vec3 v, float c)
{
	v.x *= c;
	v.y *= c;
	v.z *= c;
	return v;
}

vec3 operator/(vec3 v, float c)
{
	v.x /= c;
	v.y /= c;
	v.z /= c;
	return v;
}

vec3 operator+(vec3 v, vec3 c)
{
	v.x += c.x;
	v.y += c.y;
	v.z += c.z;
	return v;
}

vec3 operator-(vec3 v, vec3 c)
{
	v.x -= c.x;
	v.y -= c.y;
	v.z -= c.z;
	return v;
}

vec3 operator*(vec3 v, vec3 c)
{
	v.x *= c.x;
	v.y *= c.y;
	v.z *= c.z;
	return v;
}

vec3 operator/(vec3 v, vec3 c)
{
	v.x /= c.x;
	v.y /= c.y;
	v.z /= c.z;
	return v;
}