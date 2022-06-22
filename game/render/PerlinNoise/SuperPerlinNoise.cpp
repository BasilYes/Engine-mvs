#include "SuperPerlinNoise.h"
#include "math.h"

SuperPerlinNoise::SuperPerlinNoise(unsigned int sizeX, unsigned int sizeY, unsigned int startSizeX, unsigned int startSizeY, float segmentSize, int octavaCount, int seed)
	:PerlinNoise(sizeX, sizeY, segmentSize, octavaCount, seed),
	m_startSizeX(startSizeX), m_startSizeY(startSizeY)
{

}

float SuperPerlinNoise::getPoint(float x, float y)
{
	unsigned int L_segmentSize = m_segmentSize;
	int segY, segX;
	float out = 0.0f;
	float divider = 1.0f;
	for (int octava = 0; octava < m_octavaCount; octava++, L_segmentSize >>= 1)
	{
		divider *= 2.0f;

		segX = x / L_segmentSize;
		segY = y / L_segmentSize;

		float dx = (float(x - segX * L_segmentSize) + 0.5f) / float(L_segmentSize);
		float dy = (float(y - segY * L_segmentSize) + 0.5f) / float(L_segmentSize);

		Vector2f x0y0(dx	, dy	);
		Vector2f x1y0(dx - 1, dy	);
		Vector2f x0y1(dx	, dy - 1);
		Vector2f x1y1(dx - 1, dy - 1);

		int L_segmentCountX = m_startSizeX << octava;
		int L_segmentCountY = m_startSizeY << octava;

		if (L_segmentCountX > m_sizeX)
			L_segmentCountX = m_sizeX;
		if (L_segmentCountY > m_sizeY)
			L_segmentCountY = m_sizeY;

		segX = (segX + octava * 31) % L_segmentCountX;
		segY = (segY + octava * 31) % L_segmentCountY;

		float a, b, c, d;
		if (segX + 1 == L_segmentCountX)
		{
			if (segY + 1 == L_segmentCountY)
			{
				a = getNodeVector(segX, segY) * x0y0;
				b = getNodeVector(0, segY) * x1y0;
				c = getNodeVector(segX, 0) * x0y1;
				d = getNodeVector(0, 0) * x1y1;
			}
			else
			{
				a = getNodeVector(segX, segY) * x0y0;
				b = getNodeVector(0, segY) * x1y0;
				c = getNodeVector(segX, segY + 1) * x0y1;
				d = getNodeVector(0, segY + 1) * x1y1;
			}
		}
		else
		{
			if (segY + 1 == L_segmentCountY)
			{
				a = getNodeVector(segX, segY) * x0y0;
				b = getNodeVector(segX + 1, segY) * x1y0;
				c = getNodeVector(segX, 0) * x0y1;
				d = getNodeVector(segX + 1, 0) * x1y1;
			}
			else
			{
				a = getNodeVector(segX, segY) * x0y0;
				b = getNodeVector(segX + 1, segY) * x1y0;
				c = getNodeVector(segX, segY + 1) * x0y1;
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