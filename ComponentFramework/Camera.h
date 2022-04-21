#include "Matrix.h"
#include "Actor.h"
#include "Trackball.h"
#include "Skybox.h"
using namespace MATH;

class Camera : public Actor {
private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;
	Trackball* trackball;
	Skybox* skybox;

public:
	Camera(Actor* parent_);
	~Camera();
	bool OnCreate();
	void Render()const;
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getViewMatrix() { return viewMatrix; }
	void HandleEvents(const SDL_Event& sdlEvent);
	Skybox* GetSkybox() { return skybox; }

};
