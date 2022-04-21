#pragma once
#include "Component.h"
#include "Shader.h"
#include "Mesh.h"

class Skybox: public Component
{
private:
	unsigned int textureID;
	const char *posXfilename, * posYfilename,* posZfilename,* negXfilename,* negYfilename,* negZfilename;
	Mesh* mesh;
	Shader* shader;
public:
	Skybox(const char *posXfilename_, const char* posYfilename_, const char* posZfilename_,
		const char* negXfilename_, const char* negYfilename_, const char* negZfilename_);
	~Skybox();
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void Render()const override;
	Shader* GetShader() { return shader; }
	int GetTextureID() { return textureID; }
};

