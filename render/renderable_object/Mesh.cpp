#include "Mesh.h"
#include "asset/assets/model/AModel.h"
#include "asset/AManager.h"
#include "debug.h"
#include "render/RCamera.h"
#include "render/RManager.h"
#include <utility>

Mesh::Mesh(Transform transform, unsigned int modelKey, unsigned int shaderKey)
	:LocatedObject(transform), m_model{ std::move(AManager::getAManager().getModel(modelKey)) }
{
	auto& meshes = m_model->getMeshes();
	for (auto& mesh : meshes)
		m_shaders.push_back(AManager::getAManager().getShader(shaderKey));

}

Mesh::Mesh(Transform transform, unsigned int modelKey, std::vector<unsigned int> shadersKeys)
	: LocatedObject(transform), m_model{ std::move(AManager::getAManager().getModel(modelKey))}
{
	auto& meshes = m_model->getMeshes();

	ASSERT(shadersKeys.size() >= meshes.size(), "Shader array so short");
	
	for (int i = 0; i < meshes.size(); i++)
	{
		m_shaders.push_back(AManager::getAManager().getShader(shadersKeys[i]));
	}
}

void Mesh::Draw(const mat4 &view, const mat4 &proj)
{
	auto& meshes = m_model->getMeshes();
	for (int i = 0; i < meshes.size(); i++)
	{
		//RCamera* camera = RManager::
		//ñamera.initViewMatrix(view);
		//shader.setMat4("projection", proj);
		mat4 scale, rotate, transl, model, view2;
		initRotateTransform(rotate, getRotation());
		initTranslationTransform(transl, getLocation());
		initScaleTransform(scale, getScale());
		model =  proj * view * transl * rotate * scale;
		//view2 = view * proj;
		//model = proj * view * model;
		//model = model * view2;
		(*m_shaders[i]).use();
		//m_shaders[i]->setMat4("projection", proj);
		//m_shaders[i]->setMat4("view", view2);
		m_shaders[i]->setMat4("model", model);
		meshes[i].Draw(*m_shaders[i]);
	}
}
