#include "AManager.h"

ARef<AShader>::~ARef()
{
	(*m_count)--;
	if ((*m_count) == 0)
	{
		delete m_count;
		delete AManager::getAManager().m_shaders[m_key];
	}
}

ARef<AModel>::~ARef()
{
	(*m_count)--;
	if ((*m_count) == 0)
	{
		delete m_count;
		delete AManager::getAManager().m_models[m_key];
	}
}