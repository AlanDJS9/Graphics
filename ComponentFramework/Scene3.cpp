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


Scene3::Scene3(): sphere(nullptr), shader(nullptr), mesh(nullptr), earthTexture(nullptr), moonTexture(nullptr) {
	
	Debug::Info("Created Scene3: ", __FILE__, __LINE__);
}

Scene3::~Scene3() {
	Debug::Info("Deleted Scene3: ", __FILE__, __LINE__);
}

bool Scene3::OnCreate() {
	Debug::Info("Loading assets Scene3: ", __FILE__, __LINE__);
	sphere = new Actor(nullptr);
	sphere->OnCreate();

	mesh = new Mesh(nullptr, "meshes/Sphere.obj");
	mesh->OnCreate();

	shader = new Shader(nullptr, "shaders/multiLightsVert.glsl", "shaders/multiLightsFrag.glsl");
	shader->OnCreate();

	earthTexture = new Texture();
	earthTexture->LoadImage("textures/earthclouds.jpg");
	moonTexture = new Texture();
	moonTexture->LoadImage("textures/moon.jpg");
	//Lens of the camera
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	//The orientation of the projection, how we look depth
	//														//Where is the camera looking?
									//Where is the camera? (no camera actually)
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	//Setting light position x,y,z
	lightPosA = Vec3(5.0f, 1.0f, 0.0f);
	lightPosB = Vec3(0.0f, -7.0f, -5.0f);
	return true;
}

void Scene3::OnDestroy() {
	Debug::Info("Deleting assets Scene3: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	delete earthTexture;
	delete moonTexture;
}

void Scene3::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene3::Update(const float deltaTime) {
	
	static float totalTime = 0.0f;
	totalTime += deltaTime;
	earthModelMatrix = MMath::rotate(totalTime * 5.5f, Vec3(0.0f, 1.0f, 0.0f)) * 
		MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));

	moonModelMatrix = MMath::rotate(totalTime * 5.5f, Vec3(0.0f, 1.0f, 0.0f)) * 
		MMath::translate(Vec3(6.0f,0.0f,0.0f)) * //move the mooon 
		MMath::rotate(totalTime * 200.5f, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::scale(Vec3(0.27f, 0.27f,0.27f)) * //sphere size
		MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f)); //rotate moon with north pole up
	//modelMatrix = MMath::rotate(totalTime * 5.5f, Vec3(0.0f, 1.0f, 0.0f));

}

void Scene3::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	
	glUniform3fv(shader->GetUniformID("lightPosA"), 1, lightPosA);
	glUniform3fv(shader->GetUniformID("lightPosB"), 1, lightPosB);

	glBindTexture(GL_TEXTURE_2D,earthTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, earthModelMatrix);
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, moonTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, moonModelMatrix);
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);

}



	
