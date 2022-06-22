#pragma once
#include "PerlinNoise.h"
class SuperPerlinNoise :
	public PerlinNoise
{
public:
	const unsigned int m_startSizeX;//���������� ��������� �� 1 ������
	const unsigned int m_startSizeY;//���������� ��������� �� 1 ������

	virtual float getPoint(float x, float y);

	SuperPerlinNoise(unsigned int sizeX, unsigned int sizeY, unsigned int startSizeX, unsigned int startSizeY, float segmentSize, int octavaCount, int seed = 15092002);
protected:

private:
};

