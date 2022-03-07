#include "Actor.h"
#include "Texture.h"
#include "Mesh.h"

Actor::Actor(Component* parent_):Component(parent_) {}
Actor::~Actor() {}

void Actor::ListComponents() const {
	for (auto c : components) {
		std::cout << typeid(*c).name() << std::endl;
	}
}


bool Actor::OnCreate() {
	return true;
}
void Actor::OnDestroy() {
	if (texture) {
		delete texture;
	}
	if (mesh) {
		mesh->OnDestroy();
		delete mesh;
	}
}
void Actor::Update(const float deltaTime) {}
void Actor::Render()const {}






