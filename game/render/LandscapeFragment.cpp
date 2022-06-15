#include <glad/glad.h>
#include "LandscapeFragment.h"
#include "other/math/matrix.h"
#include "render/RCamera.h"
#include "asset/assets/AShader.h"

LandscapeFragment::LandscapeFragment(Transform transform, unsigned int sizeX, unsigned int sizeY)
	: LocatedObject{ transform }, m_sizeX{ sizeX }, m_sizeY{ sizeY }, m_shader{ AManager::getAManager().getShader(1) }
{
	updateMesh();
	setupSegment();
}

float func(unsigned int x, unsigned int y)
{
	return (x + y) * 0.1f;
}

void LandscapeFragment::updateMesh()
{
	m_indices.resize(3 * 2 * m_sizeX * m_sizeY);
	m_vertices.resize(m_sizeX * (2 * m_sizeY + 1) + 1);

	//Initiation vertex position
	unsigned int vertexId = 0;
	unsigned int y = 0, x = 0;
	for (y = 0; y < m_sizeY; y++)
	{
		m_vertices[vertexId].position = vec3{ 0.0f, (float)y, func(0,y) };
		vertexId++;
		for (x = 1; x < m_sizeX; x++)
		{
			m_vertices[vertexId].position = vec3{ (float)x, (float)y, func(x,y) };
			vertexId++;
			m_vertices[vertexId].position = vec3{ (float)x, (float)y, func(x,y) };
			vertexId++;
		}
		m_vertices[vertexId].position = vec3{ (float)m_sizeX, (float)y, func(m_sizeX,y) };
	}
	for (x = 0; x <= m_sizeX; x++)
	{
		m_vertices[vertexId].position = vec3{ (float)x, (float)y, func(x,y) };
		vertexId++;
	}

	//Indices initiation and normal creating
	vertexId = 0;
	for (y = 0; y < m_sizeY; y++)
	{
		for (x = 0; x < m_sizeX; x++)
		{
			m_indices[vertexId * 3] = vertexId;
			m_indices[vertexId * 3 + 1] = vertexId + m_sizeX * 2;
			m_indices[vertexId * 3 + 2] = vertexId + m_sizeX * 2 + 1;
			m_vertices[vertexId].normal = cross(m_vertices[vertexId + m_sizeX * 2].position - m_vertices[vertexId].position,
				m_vertices[vertexId + m_sizeX * 2 + 1].position - m_vertices[vertexId].position);
			vertexId++;

			m_indices[vertexId * 3] = vertexId;
			m_indices[vertexId * 3 + 1] = vertexId - 1;
			m_indices[vertexId * 3 + 2] = vertexId + m_sizeX * 2;
			m_vertices[vertexId].normal = cross(m_vertices[vertexId - 1].position - m_vertices[vertexId].position,
				m_vertices[vertexId + m_sizeX * 2].position - m_vertices[vertexId].position);
			vertexId++;

			x++;
			if (x < m_sizeX)
				break;

			m_indices[vertexId * 3] = vertexId;
			m_indices[vertexId * 3 + 1] = vertexId + m_sizeX * 2;
			m_indices[vertexId * 3 + 2] = vertexId + 1;
			m_vertices[vertexId].normal = cross(m_vertices[vertexId + m_sizeX * 2].position - m_vertices[vertexId].position,
				m_vertices[vertexId + m_sizeX + 1].position - m_vertices[vertexId].position);
			vertexId++;

			m_indices[vertexId * 3] = vertexId;
			m_indices[vertexId * 3 + 1] = vertexId + m_sizeX * 2 - 1;
			m_indices[vertexId * 3 + 2] = vertexId + m_sizeX * 2;
			m_vertices[vertexId].normal = cross(m_vertices[vertexId + m_sizeX * 2 - 1].position - m_vertices[vertexId].position,
				m_vertices[vertexId + m_sizeX * 2].position - m_vertices[vertexId].position);
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

void LandscapeFragment::draw(const RCamera* camera) const
{
	mat4 view = camera->getViewMatrix();
	mat4 scale, rotate, transl, model;

	initRotateTransform(rotate, getRotation());
	initTranslationTransform(transl, getLocation());
	initScaleTransform(scale, getScale());

	model = view * transl * rotate * scale;

	m_shader->setMat4("viewModel", model);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
