#pragma once
#include "Define.h"
#include "GameObject.h"
#include "GameMap.h"

class Item : public GameObject
{

public:
    Item();
    ~Item();
    void Update(SDL_Rect character, GameMap* MAP);
    void collisionX(GameMap* MAP);
    void collisionY(GameMap* MAP);
    void dropItem(std::vector<Item>& vItem, int numCoin, int numGem, int char_hp) const;
    void setId(int id) { this->id = id; }
    int getId() const { return this->id; }
    void setVal(int val) { this->val = val; }
    int getVal() const { return this->val; }
    bool getFell() const { return this->fell; }

protected:
    bool fell;
    int id;
    enum ID {
        COIN = 0,
        GEM = 1,
        HEART = 2,
        TREASURE = 3,
    };
    int val;
};