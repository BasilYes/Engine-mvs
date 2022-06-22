#pragma once
#include "math_2d.h"

class PerlinNoise
{
public:
	const int m_seed;
	const int m_octavaCount;//коль=ичество октав в шуме
	const float m_segmentSize;//сегменты квадратные, это длинна ребра
	const unsigned int m_sizeX;//количество сегментов по оси X
	const unsigned int m_sizeY;//количество сегментов по оси Y

	virtual float getPoint(float x, float y);

	PerlinNoise(unsigned int sizeX = 4, unsigned int sizeY = 4, float segmentSize = 64, int octavaCount = 1, int seed = 15092002);
	virtual ~PerlinNoise();

protected:
	Vector2f** getMatrix() { return m_matrix; }
	Vector2f& getNodeVector(unsigned int x, unsigned int y);
private:
	Vector2f** m_matrix;
};