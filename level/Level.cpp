#include "Level.h"
#include "Unit.h"
#include "LevelInstance.h"

///////////////

Level* Level::m_activeLevel;
void Level::init(Level* lvl)
{
	ASSERT(!m_activeLevel, "Can't Lvl reinit");
	m_activeLevel = lvl;
	lvl->load();
}

void Level::load()
{
}

void Level::updateCoreInstanse(uvec2 position)
{
	m_coreInstance = position;
	int x,y,X,Y,x0,y0,l_x,l_y,LOD;
	LOD = m_LOD;
	x = (int)position.data[0] - LOD - 1;
	y = (int)position.data[1] - LOD - 1;
	X = (int)position.data[0] + LOD + 1;
	Y = (int)position.data[1] + LOD + 1;
	x0 = (int)position.data[0];
	y0 = (int)position.data[1];

	x += m_size.data[0];
	X += m_size.data[0];
	x0 += m_size.data[0];

	y += m_size.data[1];
	Y += m_size.data[1];
	y0 += m_size.data[1];

	for (int i = x; i <= X; i++)
	{
		for (int j = y; j <= Y; j++)
		{
			l_x = i % m_size[0];
			l_y = j % m_size[1];

			if (m_instances[l_x][l_y])
			{
				if (std::sqrt((double)((i - x0) * (i - x0) + (j - y0) * (j - y0))) <= m_LOD)
				{
					m_instances[l_x][l_y]->m_offset = vec3{  m_instancesSize.data[0] * (i - x0), m_instancesSize.data[0] * (j - y0), 0.0f};
					m_instances[l_x][l_y]->updateInstanse();
				}
				else
				{
					delete m_instances[l_x][l_y];
					m_instances[l_x][l_y] = nullptr;
				}
			}
			else
			{
				if (std::sqrt((double)((i - x0) * (i - x0) + (j - y0) * (j - y0))) <= m_LOD)
				{
					m_instances[l_x][l_y] = createLevelInstance(
						vec3{ m_instancesSize.data[0] * (i - x0), m_instancesSize.data[0] * (j - y0), 0.0f },
						m_instancesSize, 
						uvec2{ (unsigned int)l_x, (unsigned int)l_y });
				}
			}
		}
	}


	//for (int x = 0; x < m_size.data[0]; x++)
	//{
	//	for (int y = 0; y < m_size.data[1]; y++)
	//	{
	//		if (m_instances[x][y])
	//			std::cout << "1" << " ";
	//		else
	//			std::cout << "0" << " ";
	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "\n";
	//std::cout << "\n";
}

void Level::tick()
{
}

Level::Level(uvec2 size, vec2 instancesSize, float LOD)
	:m_size{ size }, m_instancesSize{instancesSize}, m_LOD{LOD}
{
	m_instances = new LevelInstance * *[size.data[0]];
	for (int x = 0; x < size.data[0]; x++)
	{
		m_instances[x] = new LevelInstance * [size.data[1]];
		for (int y = 0; y < size.data[1]; y++)
			m_instances[x][y] = nullptr;
	}
}

Level::~Level()
{
	for (int x = 0; x < m_size.data[0]; x++)
	{
		for (int y = 0; y < m_size.data[1]; y++)
			if (m_instances[x][y])
				delete m_instances[x][y];
		delete[] m_instances[x];
	}
	delete[] m_instances;
}