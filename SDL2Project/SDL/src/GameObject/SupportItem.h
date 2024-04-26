#pragma once
#include "Define.h"
#include "GameObject.h"
#include "GameMap.h"
#include "Item.h"

class SupportItem : public GameObject
{
public:
    SupportItem();
    ~SupportItem();
    void loadVar(pii _idle_, pii _move_, pii _victory_);
    void update(SDL_Rect character, GameMap* MAP, std::vector<Item>& vItem);
    void show(SDL_Renderer* renderer, int view, SDL_Texture* texture);
    void collisionY(GameMap* MAP);
    bool get_done() const { return done; }
    int getStatus() const { return status; }
    int getType() const { return type; }
    void setType(int _type) { type = _type; }

protected:
    int type;
    enum TYPE {
        FLOATING = 0,
        GROUND = 1,
    };
    int status;
    enum STATUS {
        IDLE = 0,
        MOVE = 1,
        VICTORY = 2,
    };
    int frame;
    pii _idle, _move, _victory;
    bool done;
    bool dropped;
};