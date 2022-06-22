#include "math_2d.h"

float operator*(Vector2f const a, Vector2f const b)
{
	return (a.x * b.x) + (a.y * b.y);
}