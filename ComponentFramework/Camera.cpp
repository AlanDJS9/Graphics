#include "Camera.h"
#include "Matrix.h"
#include "Actor.h"
#include "MMath.h"
#include "Skybox.h"
using namespace MATH;

Camera::Camera(Actor* parent_):Actor(parent_) {
	projectionMatrix = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5f, 100.0f);
	translationMatrix = MMath::translate(Vec3(0.0f, 0.0f, -10.0f));
	rotationMatrix = MMath::rotate(0.0f, Vec3(0.0f, 1.0f, 0.0f));
	//viewMatrix = translationMatrix * rotationMatrix;
	viewMatrix =  rotationMatrix * translationMatrix;

	trackball = new Trackball();
}

Camera::~Camera() {
	if (trackball)
		delete trackball;
}

bool Camera::OnCreate() {

	skybox = new Skybox("textures/posx.jpg", "textures/posy.jpg", "textures/posz.jpg",
		"textures/negx.jpg", "textures/negy.jpg", "textures/negz.jpg");
	/*skybox = new Skybox("textures/stars/StarSkyboxPosx.png", "textures/stars/StarSkyboxPosy.png", "textures/stars/StarSkyboxPosz.png",
		"textures/stars/StarSkyboxNegx.png", "textures/stars/StarSkyboxNegY.png", "textures/stars/StarSkyboxnegz.png");
	*/bool status = skybox->OnCreate();
	return status;
}


void Camera::HandleEvents(const SDL_Event& sdlEvent) {
	trackball->HandleEvents(sdlEvent);
	rotationMatrix = trackball->getMatrix4();
	//reading matrices from CAMERA PERSEPECTIVE L -> R
	//viewMatrix = translationMatrix * rotationMatrix;
	viewMatrix = rotationMatrix * translationMatrix;
}

void Camera::Render() const {

	if (skybox) {
		glUseProgram(skybox->GetShader()->GetProgram());
		glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
		glUniformMatrix4fv(skybox->GetShader()->GetUniformID("viewMatrix"), 1, GL_FALSE, rotationMatrix);
		skybox->Render();
		glUseProgram(0);
	}
}
