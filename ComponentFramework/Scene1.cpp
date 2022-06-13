#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene1.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Scene1::Scene1(): sphere(nullptr), shader(nullptr), mesh(nullptr)  {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene1: ", __FILE__, __LINE__);
}

bool Scene1::OnCreate() {
	Debug::Info("Loading assets Scene1: ", __FILE__, __LINE__);
	sphere = new Actor(nullptr);
	sphere->OnCreate();

	mesh = new Mesh(nullptr, "meshes/Mario.obj");
	mesh->OnCreate();

	shader = new Shader(nullptr, "shaders/multiLightsVert.glsl", "shaders/multiLightsFrag.glsl");
	shader->OnCreate();

	texture = new Texture();
	texture->LoadImage("textures/mario_mime.png");
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	//The orientation of the projection, how we look depth
	//														//Where is the camera looking?
									//Where is the camera? (no camera actually)
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	modelMatrix.loadIdentity();
	//Setting light position x,y,z
	lightPosA = Vec3(50.0f, 10.0f, 0.0f);
	lightPosB = Vec3(-50.0f, 10.0f, 0.0f);
	return true;
}

void Scene1::OnDestroy() {
	Debug::Info("Deleting assets Scene1: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	delete texture;

}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
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

void Scene1::Update(const float deltaTime) {
	
	static float totalTime = 0.0f;
	totalTime += deltaTime;
	modelMatrix = MMath::rotate(totalTime * 50.5f, Vec3(0.0f, 1.0f, 0.0f));

}

void Scene1::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	
	glUniform3fv(shader->GetUniformID("lightPosA"), 1, lightPosA);
	glUniform3fv(shader->GetUniformID("lightPosB"), 1, lightPosB);

	glBindTexture(GL_TEXTURE_2D,texture->getTextureID());
	mesh->Render(GL_LINES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);

}



	
