#include "RMesh.h"
#include "asset/assets/model/AModel.h"
#include "asset/AManager.h"
#include "debug.h"
#include "render/RCamera.h"
#include "render/RManager.h"
#include <utility>

RMesh::RMesh(unsigned int modelKey, unsigned int shaderKey)
	: RObject{}
	, m_model{ std::move(AManager::getAManager().getModel(modelKey)) }
{
	auto& meshes = m_model->getMeshes();
	for (auto& mesh : meshes)
		m_shaders.push_back(AManager::getAManager().getShader(shaderKey));

}

RMesh::RMesh(unsigned int modelKey, std::vector<unsigned int> shadersKeys)
	: RObject{}
	, m_model{ std::move(AManager::getAManager().getModel(modelKey)) }
{
	auto& meshes = m_model->getMeshes();

	ASSERT(shadersKeys.size() >= meshes.size(), "Shader array so short");

	for (int i = 0; i < meshes.size(); i++)
	{
		m_shaders.push_back(AManager::getAManager().getShader(shadersKeys[i]));
	}
}

void RMesh::draw(const RCamera* camera) const
{
	mat4 view = camera->getViewMatrix();
	mat4 scale, rotate, transl, model;

	initRotateTransform(rotate, getRotation());
	initTranslationTransform(transl, getLocation());
	initScaleTransform(scale, getScale());

	model = view * transl * rotate * scale;

	auto& meshes = m_model->getMeshes();
	for (int i = 0; i < meshes.size(); i++)
	{
		(*m_shaders[i]).use();
		m_shaders[i]->setMat4("viewModel", model);
		meshes[i].Draw(*m_shaders[i]);
	}
}