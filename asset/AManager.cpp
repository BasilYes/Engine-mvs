#include "AManager.h"
#include "assets/AShader.h"
#include "assets/model/AModel.h"
#include <debug.h>

AManager* AManager::m_AManager = nullptr;


constexpr unsigned int modelCount = 3;
constexpr unsigned int shaderCount = 2;
void AManager::init()
{
	ASSERT(!m_AManager, "AssetManager reinitialization")
	ARef<AModel>** models = new ARef<AModel>*[modelCount];
	ARef<AShader>** shaders = new ARef<AShader>*[shaderCount];
	for (int i = 0; i < modelCount; i++)
		models[i] = nullptr;
	for (int i = 0; i < shaderCount; i++)
		shaders[i] = nullptr;
	m_AManager = new AManager{models, shaders};
}
ARef<AShader> AManager::getShader(unsigned int key)
{
	if (!m_shaders[key])
	{
		m_shaders[key] = new ARef<AShader>{ new AShader(key), key};
	}
	return ARef<AShader>{*(m_shaders[key])};
}
ARef<AModel> AManager::getModel(unsigned int key)
{
	if (!m_models[key])
	{
		m_models[key] = new ARef<AModel>{ new AModel(key), key };
	}
	return ARef<AModel>{*(m_models[key])};
}

AManager::AManager(ARef<AModel>** models, ARef<AShader>** shaders)
	:m_models{models}, m_shaders{shaders}
{
}

AManager::~AManager()
{
	delete[] m_models;
	delete[] m_shaders;
}
