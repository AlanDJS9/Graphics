#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene4.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

Scene4::Scene4() : sphere(nullptr), shader(nullptr), camera(nullptr) {

	Debug::Info("Created Scene4: ", __FILE__, __LINE__);
}

Scene4::~Scene4() {
	Debug::Info("Deleted Scene4: ", __FILE__, __LINE__);
	delete camera;

}

bool Scene4::OnCreate() {
	Debug::Info("Loading assets Scene4: ", __FILE__, __LINE__);
	camera = new Camera(nullptr);
	camera->OnCreate();

	sphere = new Actor(nullptr);
	sphere->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	sphere->GetMesh()->OnCreate();

	sphere->OnCreate();

	shader = new Shader(nullptr, "shaders/reflectionVert.glsl", "shaders/noiseFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed";
	}

	return true;
}

void Scene4::OnDestroy() {
	Debug::Info("Deleting assets Scene4: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	shader->OnDestroy();
	delete shader;

}

void Scene4::HandleEvents(const SDL_Event& sdlEvent) {
	camera->HandleEvents(sdlEvent);

	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			//Changed this to get a closer look, everything is now working. it was just a little far
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

	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}
void Scene4::Update(const float deltaTime) {
	
	
}

void Scene4::Render() const {
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
	
	glBindTexture(GL_TEXTURE_2D, camera->GetSkybox()->GetTextureID());
	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkybox()->GetTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	sphere->GetMesh()->Render(GL_TRIANGLES);
	
	glUseProgram(0);

}

	
