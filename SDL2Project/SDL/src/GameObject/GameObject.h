#pragma once
#include "Define.h" 

class GameObject {
public:
	GameObject();
	~GameObject();
    void setRect(const int& x, const int& y) { rect.x = x, rect.y = y; }
    void setRect(SDL_Rect rect) { this->rect = rect; }
    SDL_Rect getRect() { return rect; }
    SDL_Texture* getObject() { return pObject; }

    bool loadImage(std::string path, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, int view);
    void Free();

    int getX() { return rect.x; }
    int getY() { return rect.y; }
    int getW() { return rect.w; }
    int getH() { return rect.h; }
    int getVelX() { return velX; }
    int getVelY() { return velY; }
    int getHp() { return hp; }
    int getDmg() { return dmg; }
    int getMaxHp() { return maxHp; }
    int getLevel() { return level; }
    int getBaseDmg() { return baseDmg; }
    int getBaseHp() { return baseHp; }
    int getObjectId() { return objectId; }

    void setX(int x) { rect.x = x; }
    void setY(int y) { rect.y = y; }
    void setW(int w) { rect.w = w; }
    void setH(int h) { rect.h = h; }
    void setVelX(int velX) { this->velX = velX; }
    void setVelY(int velY) { this->velY = velY; }
    void setHp(int hp) { this->hp = min(max(hp, 0), maxHp); }
    void setDmg(int dmg) { this->dmg = dmg; }
    void setMaxHp(int maxHp) { this->maxHp = maxHp; }
    void setLevel(int level) { this->level = level; }
    void setObjectId(int objectId, bool ok) { if (this->objectId == 0 || ok) this->objectId = objectId; }

    void takeDamage(int damage) { hp = max(0, hp - damage); }
protected:
    SDL_Texture* pObject;
	SDL_Rect rect;
	int velX, velY;
	int hp, dmg;
	int maxHp;
	int level;
	int baseHp, baseDmg;
	int objectId;
};