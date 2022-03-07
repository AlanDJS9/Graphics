#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"

#include "Vector.h"
#include "Matrix.h"
using namespace MATH;
class Texture;

/// Forward declarations 
union SDL_Event;
class Actor;
class Mesh;
class Shader;

class Scene1 : public Scene {
private:
	//Need to delete pointer
	Actor* sphere;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;

	//Created on the stack, will disapear when program exits
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	Vec3 lightPosA;
	Vec3 lightPosB;
public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE1_H