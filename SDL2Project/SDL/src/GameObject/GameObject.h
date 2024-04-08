#pragma once
#include "Define.h"

class GameObject {
public:
	GameObject();
	~GameObject();
    void setRect(const int& x, const int& y) { rect.x = x, rect.y = y; }
    void setRect(SDL_Rect _rect) { rect = _rect; }
    SDL_Rect getRect() { return rect; }
    //std::shared_ptr<Sprite2D> getObject() { return pObject; }

    //void loadImage(std::string path);
    //void render(int x, int y, int width, int height, int view);
    //void Free();

    int getX() { return rect.x; }
    int getY() { return rect.y; }
    int getW() { return rect.w; }
    int getH() { return rect.h; }
    double getVelX() { return velX; }
    double getVelY() { return velY; }
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
    void setVelX(double _velX) { velX = _velX; }
    void setVelY(double _velY) { velY = _velY; }
    void setHp(int _hp) { hp = min(max(_hp, 0), maxHp); }
    void setDmg(int _dmg) { dmg = _dmg; }
    void setMaxHp(int _maxHp) { maxHp = _maxHp; }
    void setLevel(int _level) { level = _level; }
    void setObjectId(int _objectId, bool ok) { if (objectId == 0 || ok) objectId = _objectId; }
    void takeDamage(int damage) { hp = max(0, hp - damage); }
protected:
    //SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();
	//std::shared_ptr<Sprite2D> pObject;
	SDL_Rect rect;
	double velX, velY;
	int hp, dmg;
	int maxHp;
	int level;
	int baseHp, baseDmg;
	int objectId;
};