#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene2.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Randomizer.h"

Scene2::Scene2(): skull(nullptr), shader(nullptr), leftEye(nullptr),rightEye(nullptr), thirdEye(nullptr) {
	Debug::Info("Created Scene2: ", __FILE__, __LINE__);
	trackball = new Trackball();

}

Scene2::~Scene2() {
	Debug::Info("Deleted Scene2: ", __FILE__, __LINE__);
}

bool Scene2::OnCreate() {
	Debug::Info("Loading assets Scene2: ", __FILE__, __LINE__);

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
	leftEye->SetModelMatrix(MMath::translate(Vec3(-0.6f,0.25f,0.85f)) *
							MMath::scale(0.4f,0.4f,0.4f)	);

	rightEye = new Actor(skull);
	rightEye->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	rightEye->GetMesh()->OnCreate();
	rightEye->SetTexture(new Texture());
	rightEye->GetTexture()->LoadImage("textures/evilEye.jpg");
	rightEye->OnCreate();						//x		y		z
	rightEye->SetModelMatrix(MMath::translate(Vec3(0.5f, 0.25f, 0.85f)) *
		MMath::scale(0.4f, 0.4f, 0.4f));

	thirdEye = new Actor(skull);
	thirdEye->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	thirdEye->GetMesh()->OnCreate();
	thirdEye->SetTexture(new Texture());
	thirdEye->GetTexture()->LoadImage("textures/evilEye.jpg");
	thirdEye->OnCreate();						//x		y		z
	thirdEye->SetModelMatrix(MMath::translate(Vec3(0.0f, 1.2f, 0.85f)) *
		MMath::scale(0.4f, 0.4f, 0.4f));


	
	shader = new Shader(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	shader->OnCreate();


	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	//The orientation of the projection, how we look depth
									//Where is the camera? (no camera actually)
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));


	skull->GetModelMatrix().loadIdentity();
	lightPos = Vec3(0.0f, 0.0f, 0.0f);
	return true;
}

void Scene2::OnDestroy() {
	Debug::Info("Deleting assets Scene2: ", __FILE__, __LINE__);
	skull->OnDestroy();
	delete skull;

	shader->OnDestroy();
	delete shader;

}

void Scene2::HandleEvents(const SDL_Event &sdlEvent) {
	trackball->HandleEvents(sdlEvent);
	skull->SetModelMatrix(trackball->getMatrix4());



	switch( sdlEvent.type ) {
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

void Scene2::Update(const float deltaTime) {
	Randomizer r;
	Randomizer y;
	Randomizer x;


	trackballInput = MMath::transpose(trackball->getMatrix4());
	

		crazyEyeRotation = MMath::rotate(r.rand(0.0f, -90.0f), Vec3(x.rand(0.0f, 1.0f), y.rand(0.0f, 20.0f), 0.0f));
		thirdEyeCombinedMatrix = skull->GetModelMatrix() * thirdEye->GetModelMatrix() * trackballInput * crazyEyeRotation;

	//Eyes keep straring at the camera
	leftEyeCombinedMatrix = skull->GetModelMatrix() * leftEye->GetModelMatrix() * trackballInput * baseEyeRotation;
	rightEyeCombinedMatrix = skull->GetModelMatrix() * rightEye->GetModelMatrix() * trackballInput * baseEyeRotation;

}

void Scene2::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, skull->GetTexture()->getTextureID());
	skull->GetMesh()->Render(GL_TRIANGLES);


	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, leftEyeCombinedMatrix);
	glBindTexture(GL_TEXTURE_2D, leftEye->GetTexture()->getTextureID());
	leftEye->GetMesh()->Render(GL_TRIANGLES);


	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, rightEyeCombinedMatrix);
	glBindTexture(GL_TEXTURE_2D, rightEye->GetTexture()->getTextureID());
	rightEye->GetMesh()->Render(GL_TRIANGLES);


	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, thirdEyeCombinedMatrix);
	glBindTexture(GL_TEXTURE_2D, thirdEye->GetTexture()->getTextureID());
	thirdEye->GetMesh()->Render(GL_TRIANGLES);


	glUseProgram(0);

}



	
