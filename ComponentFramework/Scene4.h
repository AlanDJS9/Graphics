#ifndef SCENE4_H
#define SCENE4_H
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
class Texture;
class Camera;

class Scene4 : public Scene {
private:
	//Need to delete pointer
	Actor* sphere;
	Shader* shader;
	Camera* camera;
	//Created on the stack, will disapear when program exits
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;

public:
	explicit Scene4();
	virtual ~Scene4();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // Scene3_H