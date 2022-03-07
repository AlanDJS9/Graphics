#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Texture.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Actor;
class Mesh;
class Shader;

class Scene2 : public Scene {
private:
	//Need to delete pointer
	Actor* skull;
	Actor* leftEye;
	Shader* shader;
	//Created on the stack, will disapear when program exits
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Vec3 lightPos;

public:
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // Scene2_H