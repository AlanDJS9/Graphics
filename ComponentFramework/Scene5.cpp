#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene5.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Noise.h"
#include "SDL_gamecontroller.h"
using namespace std;
Scene5::Scene5() : sphere(nullptr), shader(nullptr), camera(nullptr) {

	Debug::Info("Created Scene5: ", __FILE__, __LINE__);
}

Scene5::~Scene5() {
	Debug::Info("Deleted Scene5: ", __FILE__, __LINE__);
	delete camera;

}

bool Scene5::OnCreate() {
	Debug::Info("Loading assets Scene5: ", __FILE__, __LINE__);
	noiseTextureID = CreateNoise3D();

	camera = new Camera(nullptr);
	camera->OnCreate();

	sphere = new Actor(nullptr);
	sphere->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	sphere->GetMesh()->OnCreate();


	shader = new Shader(nullptr, "shaders/noiseVert.glsl", "shaders/reflectionFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed";
	}

	sphere->OnCreate();
	sphere->SetModelMatrix(MMath::scale(Vec3(2.0f, 2.0f, 2.0f)));

	return true;
}

void Scene5::OnDestroy() {
	Debug::Info("Deleting assets Scene5: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	shader->OnDestroy();
	delete shader;

	//I'm not going to leave all the noise memory hanging, Scott sounded menancing jaja
	DeleteNoise3D();
}

void Scene5::HandleEvents(const SDL_Event& sdlEvent) {
	camera->HandleEvents(sdlEvent);

	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 1.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(-10.0f, Vec3(0.0f, 1.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP) {
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(-10.0f, Vec3(1.0f, 0.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN) {
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(10.0f, Vec3(1.0f, 0.0f, 0.0f)));

		}
		break;


	case SDL_CONTROLLERDEVICEADDED:
	{
		const int joystickIndex = sdlEvent.cdevice.which;
		SDL_GameController* gameController = SDL_GameControllerOpen(joystickIndex);
		SDL_Joystick* joystick = SDL_GameControllerGetJoystick(gameController);
		 SDL_JoystickID joystickID = SDL_JoystickInstanceID(joystick);
		// TODO
	}
	break;
	case SDL_CONTROLLERDEVICEREMOVED:
	{
		const SDL_JoystickID joystickID = sdlEvent.cdevice.which;
		// TODO
	}
	break;
	case SDL_CONTROLLERAXISMOTION:
	{
		const SDL_JoystickID joystickID = sdlEvent.caxis.which;
		const SDL_GameControllerAxis axis = (SDL_GameControllerAxis)sdlEvent.caxis.axis;
		const float value = sdlEvent.caxis.value / (float)SDL_JOYSTICK_AXIS_MAX;
		cout << value << endl;
		// TODO
	}
	break;
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
	{
		const SDL_JoystickID joystickID = sdlEvent.cbutton.which;
		const SDL_GameControllerButton button = (SDL_GameControllerButton)sdlEvent.cbutton.button;
		const bool isPressed = sdlEvent.cbutton.state == SDL_PRESSED;
		// TODO
	}
	break;

	default:
		break;
	}
}
void Scene5::Update(const float deltaTime) {
	//totalTime = deltaTime;
	offset.x += 0.001f;
	offset.y += 0.001f;
	offset.z += 0.005f;

	
}

void Scene5::Render() const {
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->Render();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera -> getViewMatrix());
	
	//(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	//glUniform1f(shader->GetUniformID("totalTime"), totalTime);
	glUniform3fv(shader->GetUniformID("offset"), 1, offset);

	glBindTexture(GL_TEXTURE_3D, noiseTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkybox()->GetTextureID());
	sphere->Render();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindTexture(GL_TEXTURE_3D, 0);

//	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	
	glUseProgram(0);

}

	
