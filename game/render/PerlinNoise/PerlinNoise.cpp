#include "PerlinNoise.h"
#include "math.h"
#include <random>
#include <cmath>

PerlinNoise::PerlinNoise(unsigned int sizeX, unsigned int sizeY, float segmentSize, int octavaCount, int seed)
	:m_sizeX(sizeX), m_sizeY(sizeY), m_segmentSize(segmentSize), m_octavaCount(octavaCount), m_seed(seed)
{
	std::mt19937 rand(seed);
	m_matrix = new Vector2f*[sizeX];
	float angle;
	for (int x = 0; x < sizeX; x++)
	{
		m_matrix[x] = new Vector2f[sizeY];
		for (int y = 0; y < sizeY; y++)
		{
			angle = float(0.0000000004656612873077392578125 * rand()) * 3.141592653589793;
			m_matrix[x][y].x = std::sin(angle);
			m_matrix[x][y].y = std::cos(angle);
		}
	}
}


Vector2f& PerlinNoise::getNodeVector(unsigned int x, unsigned int y)
{
	return m_matrix[x][y];
}

float PerlinNoise::getPoint(float x, float y)
{
	unsigned int L_segmentSize = m_segmentSize;
	int segY, segX;
	float out = 0.0f;
	float divider = 1.0f;
	for (int counter = 0; counter < m_octavaCount; counter++, L_segmentSize >>= 1)
	{
		divider *= 2.0f;

		segX = x / L_segmentSize;
		segY = y / L_segmentSize;

		float dx = (float(x - segX * L_segmentSize) + 0.5f) / float(L_segmentSize);
		float dy = (float(y - segY * L_segmentSize) + 0.5f) / float(L_segmentSize);

		Vector2f x0y0(dx    , dy	);
		Vector2f x1y0(dx - 1, dy	);
		Vector2f x0y1(dx	, dy - 1);
		Vector2f x1y1(dx - 1, dy - 1);

		segX %= m_sizeX;
		segY %= m_sizeY;

		float a, b, c, d;
		if (segX + 1 == m_sizeX)
		{
			if (segY + 1 == m_sizeY)
			{
				a = getNodeVector(segX, segY) * x0y0;
				b = getNodeVector(0   , segY) * x1y0;
				c = getNodeVector(segX, 0   ) * x0y1;
				d = getNodeVector(0   , 0   ) * x1y1;
			}
			else
			{
				a = getNodeVector(segX, segY    ) * x0y0;
				b = getNodeVector(0   , segY    ) * x1y0;
				c = getNodeVector(segX, segY + 1) * x0y1;
				d = getNodeVector(0   , segY + 1) * x1y1;
			}
		}
		else
		{
			if (segY + 1 == m_sizeY)
			{
				a = getNodeVector(segX    , segY) * x0y0;
				b = getNodeVector(segX + 1, segY) * x1y0;
				c = getNodeVector(segX    , 0   ) * x0y1;
				d = getNodeVector(segX + 1, 0   ) * x1y1;
			}
			else
			{
				a = getNodeVector(segX    , segY    ) * x0y0;
				b = getNodeVector(segX + 1, segY    ) * x1y0;
				c = getNodeVector(segX    , segY + 1) * x0y1;
				d = getNodeVector(segX + 1, segY + 1) * x1y1;
			}
		}
		
		dx = smooth(dx);
		dy = smooth(dy);

		float L_out = lerp(lerp(a, b, dx), lerp(c, d, dx), dy);

		out += L_out / divider;
	}

	return out / (1.0f - (1.0f / divider));
}

PerlinNoise::~PerlinNoise()
{
	for (int x = 0; x < m_sizeX; x++)
	{
		delete[] m_matrix[x];
	}
	delete[] m_matrix;
}