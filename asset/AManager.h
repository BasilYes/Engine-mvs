#pragma once
#include "ARef.h"

class AShader;
class AModel;

class AManager
{
public:
	static void init();
	static AManager& getAManager() { return *m_AManager; }
	ARef<AShader> getShader(unsigned int key);
	ARef<AModel> getModel(unsigned int key);
private:
	ARef<AModel>** m_models;
	ARef<AShader>** m_shaders;
	static AManager* m_AManager;

	AManager(ARef<AModel>** models, ARef<AShader>** shaders);
	~AManager();

	friend class ARef<AShader>;
	friend class ARef<AModel>;
};