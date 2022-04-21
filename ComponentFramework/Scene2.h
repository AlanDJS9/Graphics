#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Texture.h"
#include "Trackball.h"

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
	Actor* rightEye;
	Actor* thirdEye;


	Shader* shader;
	//Created on the stack, will disapear when program exits
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 trackballInput;
	Matrix4 leftEyeCombinedMatrix;
	Matrix4 rightEyeCombinedMatrix;
	Matrix4 thirdEyeCombinedMatrix;


	Matrix4 baseEyeRotation = MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f));
	Matrix4 crazyEyeRotation;

	Trackball* trackball;
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