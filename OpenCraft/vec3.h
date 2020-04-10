#pragma once
struct vec3
{
	float x, y, z;
	vec3();
	vec3(float xx, float yy, float zz);
	void operator+=(vec3 c);
	void operator-=(vec3 c);
	void operator*=(vec3 c);
	void operator/=(vec3 c);
	void operator+=(int c);
	void operator-=(int c);
	void operator*=(int c);
	void operator/=(int c);
	void operator+=(float c);
	void operator-=(float c);
	void operator*=(float c);
	void operator/=(float c);
	void normalize();
	vec3 to_RAD();
	float length();
};

vec3 operator+(vec3 v, int c);
vec3 operator-(vec3 v, int c);
vec3 operator*(vec3 v, int c);
vec3 operator/(vec3 v, int c);
vec3 operator+(vec3 v, float c);
vec3 operator-(vec3 v, float c);
vec3 operator*(vec3 v, float c);
vec3 operator/(vec3 v, float c);
vec3 operator+(vec3 v, vec3 c);
vec3 operator-(vec3 v, vec3 c);
vec3 operator*(vec3 v, vec3 c);
vec3 operator/(vec3 v, vec3 c);
bool operator==(vec3 v, vec3 c);

vec3 two_angles_to_vec3(float x, float y);