#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene3.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

Scene3::Scene3() : skull(nullptr), shader(nullptr), camera(nullptr), leftEye(nullptr) {

	Debug::Info("Created Scene3: ", __FILE__, __LINE__);
}

Scene3::~Scene3() {
	Debug::Info("Deleted Scene3: ", __FILE__, __LINE__);
	delete camera;

}

bool Scene3::OnCreate() {
	Debug::Info("Loading assets Scene3: ", __FILE__, __LINE__);
	camera = new Camera(nullptr);
	camera->OnCreate();

	skull = new Actor(nullptr);
	skull->SetMesh(new Mesh(nullptr, "meshes/Skull.obj"));
	skull->GetMesh()->OnCreate();
	skull->SetTexture(new Texture());
	skull->GetTexture()->LoadImage("textures/skull_texture.jpg");
	skull->OnCreate();

	leftEye = new Actor(skull);
	leftEye->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	leftEye->GetMesh()->OnCreate();
	leftEye->SetTexture(new Texture());
	leftEye->GetTexture()->LoadImage("textures/evilEye.jpg");
	leftEye->OnCreate();						//x		y		z
	leftEye->SetModelMatrix(MMath::translate(Vec3(-0.6f, 0.25f, 0.85f)) *
		MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::scale(0.4f, 0.4f, 0.4f)
	);

	shader = new Shader(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed";
	}


	lightPos = Vec3(0.0f, 0.0f, 0.0f);
	return true;
}

void Scene3::OnDestroy() {
	Debug::Info("Deleting assets Scene3: ", __FILE__, __LINE__);
	skull->OnDestroy();
	delete skull;

	shader->OnDestroy();
	delete shader;

}

void Scene3::HandleEvents(const SDL_Event& sdlEvent) {
	camera->HandleEvents(sdlEvent);

	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(10.0f, Vec3(0.0f, 1.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(-10.0f, Vec3(0.0f, 1.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP) {
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(-10.0f, Vec3(1.0f, 0.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN) {
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(10.0f, Vec3(1.0f, 0.0f, 0.0f)));

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
void Scene3::Update(const float deltaTime) {
	
	
}

void Scene3::Render() const {
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
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, skull->GetTexture()->getTextureID());
	//skull->GetMesh()->Render(GL_TRIANGLES);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix() * leftEye->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, leftEye->GetTexture()->getTextureID());
	//leftEye->GetMesh()->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

}

	
