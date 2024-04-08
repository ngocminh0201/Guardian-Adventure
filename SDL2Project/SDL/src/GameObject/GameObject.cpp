#include "GameObject.h"

GameObject::GameObject() {
	//pObject = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	velX = velY = 0;
	hp = dmg = 0;
	level = 1;
	objectId = 0;
}

GameObject::~GameObject() {

}

/*void GameObject::loadImage(std::string path) {
	auto texture = ResourceManagers::GetInstance()->GetTexture(path);
	pObject = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
}

void GameObject::render(int x, int y, int width, int height, int view)
{
	pObject->SetSize(width, height);
	pObject->Set2DPosition(x - view, y);
	pObject->Draw(renderer);

}*/
