#include <glad/glad.h>
#include "LandscapeFragment.h"
#include "other/math/matrix.h"
#include "render/RCamera.h"
#include "asset/assets/AShader.h"
#include "PerlinNoise/SuperPerlinNoise.h"

LandscapeFragment::LandscapeFragment(Transform transform, vec3 offset, unsigned int sizeX, unsigned int sizeY)
	: LocatedObject{ transform }, m_offset{ offset }, m_sizeX{sizeX}, m_sizeY{sizeY}, m_shader{ AManager::getAManager().getShader(1) }
{
	updateMesh();
	setupSegment();
}

LandscapeFragment::~LandscapeFragment()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

float func(unsigned int x, unsigned int y)
{
	static SuperPerlinNoise Noise(32, 32, 4, 4, 512, 8, 1);
	return (int)(Noise.getPoint(x % 2048, y % 2048) * 200.0f) / 2.0f;
}

void LandscapeFragment::updateMesh()
{
	m_indices.resize(2 * 3 * m_sizeX * m_sizeY);
	m_vertices.resize(m_sizeY * (2 * m_sizeX + 1) + 1);

	//Initiation vertex position
	unsigned int vertexId = 0;
	unsigned int y = 0, x = 0;
	for (x = 0; x < m_sizeX; x++)
	{
		m_vertices[vertexId].position = vec3{ (float)x, 0.0f, func(x + m_offset.data[0],m_offset.data[1]) - m_offset.data[2] };
		vertexId++;
		for (y = 1; y < m_sizeY; y++)
		{
			m_vertices[vertexId].position = vec3{ (float)x, (float)y, func(x + m_offset.data[0],y + m_offset.data[1]) - m_offset.data[2] };
			vertexId++;
			m_vertices[vertexId].position = vec3{ (float)x, (float)y, func(x + m_offset.data[0],y + m_offset.data[1]) - m_offset.data[2] };
			vertexId++;
		}
		m_vertices[vertexId].position = vec3{ (float)x, (float)m_sizeY, func(x + m_offset.data[0], m_sizeY + m_offset.data[1]) - m_offset.data[2] };
		vertexId++;
	}
	for (y = 0; y <= m_sizeY; y++)
	{
		m_vertices[vertexId].position = vec3{ (float)x, (float)y, func(x + m_offset.data[0],y + m_offset.data[1]) - m_offset.data[2] };
		vertexId++;
	}

	//Indices initiation and normal creating
	vertexId = 0;
	for (x = 1; x < m_sizeX; x++)
	{
		for (y = 0; y < m_sizeY; y++)
		{
			if ((y + x) % 2)
			{
				m_indices[vertexId * 3] = vertexId + m_sizeY * 2;
				m_indices[vertexId * 3 + 1] = vertexId + m_sizeY * 2 + 1;
				m_indices[vertexId * 3 + 2] = vertexId;
				m_vertices[vertexId].normal = cross(m_vertices[vertexId + m_sizeY * 2].position - m_vertices[vertexId].position,
					m_vertices[vertexId + m_sizeY * 2 + 1].position - m_vertices[vertexId].position).normalize();
				vertexId++;

				m_indices[vertexId * 3] = vertexId - 1;
				m_indices[vertexId * 3 + 1] = vertexId + m_sizeY * 2;
				m_indices[vertexId * 3 + 2] = vertexId;
				m_vertices[vertexId].normal = cross(m_vertices[vertexId - 1].position - m_vertices[vertexId].position,
					m_vertices[vertexId + m_sizeY * 2].position - m_vertices[vertexId].position).normalize();
				vertexId++;
			}
			else
			{
				m_indices[vertexId * 3] = vertexId + m_sizeY * 2;
				m_indices[vertexId * 3 + 1] = vertexId + 1;
				m_indices[vertexId * 3 + 2] = vertexId;
				m_vertices[vertexId].normal = cross(m_vertices[vertexId + m_sizeY * 2].position - m_vertices[vertexId].position,
					m_vertices[vertexId + 1].position - m_vertices[vertexId].position).normalize();
				vertexId++;

				m_indices[vertexId * 3] = vertexId + m_sizeY * 2 - 1;
				m_indices[vertexId * 3 + 1] = vertexId + m_sizeY * 2;
				m_indices[vertexId * 3 + 2] = vertexId;
				m_vertices[vertexId].normal = cross(m_vertices[vertexId + m_sizeY * 2 - 1].position - m_vertices[vertexId].position,
					m_vertices[vertexId + m_sizeY * 2].position - m_vertices[vertexId].position).normalize();
				vertexId++;
			}
		}
	}
	unsigned int lastRaw = 2 * m_sizeX * m_sizeY;
	for (y = 0; y < m_sizeY; y++)
	{
		if ((y + x) % 2)
		{
			m_indices[vertexId * 3] = lastRaw;
			m_indices[vertexId * 3 + 1] = lastRaw + 1;
			m_indices[vertexId * 3 + 2] = vertexId;
			m_vertices[vertexId].normal = cross(m_vertices[lastRaw].position - m_vertices[vertexId].position,
				m_vertices[lastRaw + 1].position - m_vertices[vertexId].position).normalize();
			vertexId++; lastRaw++;

			m_indices[vertexId * 3] = vertexId - 1;
			m_indices[vertexId * 3 + 1] = lastRaw;
			m_indices[vertexId * 3 + 2] = vertexId;
			m_vertices[vertexId].normal = cross(m_vertices[vertexId - 1].position - m_vertices[vertexId].position,
				m_vertices[lastRaw].position - m_vertices[vertexId].position).normalize();
			vertexId++;
		}
		else
		{
			m_indices[vertexId * 3] = lastRaw;
			m_indices[vertexId * 3 + 1] = vertexId + 1;
			m_indices[vertexId * 3 + 2] = vertexId;
			m_vertices[vertexId].normal = cross(m_vertices[lastRaw].position - m_vertices[vertexId].position,
				m_vertices[vertexId + 1].position - m_vertices[vertexId].position).normalize();
			vertexId++; lastRaw++;

			m_indices[vertexId * 3] = lastRaw - 1;
			m_indices[vertexId * 3 + 1] = lastRaw;
			m_indices[vertexId * 3 + 2] = vertexId;
			m_vertices[vertexId].normal = cross(m_vertices[lastRaw - 1].position - m_vertices[vertexId].position,
				m_vertices[lastRaw].position - m_vertices[vertexId].position).normalize();
			vertexId++;
		}
	}
}

void LandscapeFragment::setupSegment()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));

	glBindVertexArray(0);
}

void LandscapeFragment::draw(RCamera* camera) const
{
	mat4 view = camera->getViewMatrix();
	mat4 scale, rotate, transl, model;

	initRotateTransform(rotate, getRotation());
	initTranslationTransform(transl, getLocation());
	initScaleTransform(scale, getScale());

	model = view * transl * rotate * scale;

	m_shader->use();
	m_shader->setMat4("viewModel", model);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
