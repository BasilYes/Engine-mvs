#pragma once

struct Vector2f
{
	float x = 0;
	float y = 0;

	Vector2f()
	{
	}

	Vector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

float operator*(Vector2f const a, Vector2f const b);