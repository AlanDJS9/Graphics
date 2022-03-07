#ifndef SCENEPLANET_H
#define SCENEPLANET_H
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

class ScenePlanet : public Scene {
private:
	//Need to delete pointer
	Actor* sphere;
	Mesh* mesh;
	Shader* shader;
	Texture* moonTexture;
	Texture* earthTexture;

	//Created on the stack, will disapear when program exits
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 earthModelMatrix;
	Matrix4 moonModelMatrix;

	Vec3 lightPosA;
	Vec3 lightPosB;
public:
	explicit ScenePlanet();
	virtual ~ScenePlanet();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // ScenePlanet_H