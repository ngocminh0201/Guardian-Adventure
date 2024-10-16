#include "GameObject.h"

GameObject::GameObject() {
	pObject = NULL;
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
	Free();
}

bool GameObject::loadImage(std::string path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s!\n", path.c_str());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        //pObject = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            //SDL_FreeSurface(loadedSurface);
        }
        else
        {
            rect.w = loadedSurface->w;
            rect.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    pObject = newTexture;

    /*if (pObject != NULL) {
        SDL_DestroyTexture(newTexture);
        newTexture = NULL;
        return true;
    }
    return false;*/
    return pObject != NULL;
}

void GameObject::render(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = { rect.x - view, rect.y, rect.w, rect.h };

    SDL_RenderCopy(renderer, pObject, NULL, &nRect);
}

void GameObject::Free() {
    if (pObject != NULL)
    {
        SDL_DestroyTexture(pObject);
        pObject = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}