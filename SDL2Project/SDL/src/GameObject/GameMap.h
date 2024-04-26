#pragma once
#include "Define.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Sprite2D.h"
#include "ResourceManagers.h"

class GameMap {
public:
    GameMap();
    ~GameMap();
    bool loadMap(std::string path, SDL_Renderer* renderer, int level);
    void render(SDL_Renderer* renderer, int view, bool map_cleared, bool isBossLevel);
    void setNumBlock(int Num_Block) { this->Num_Block = Num_Block; }
    int getNumBlock() const { return this->Num_Block; }
    void setNumDecor(int Num_Decor) { this->Num_Decor = Num_Decor; }
    int getNumDecor() const { return this->Num_Decor; }

    void setNumCoin(int numCoin) { this->numCoin = numCoin; }
    int getNumCoin() const { return this->numCoin; }

    void setNumGem(int numGem) { this->numGem = numGem; }
    int getNumGem() const { return this->numGem; }

    int** getInfo() { return this->info; }
    int getVictory() const { return this->victory_w; }
    int getMapWidth() const { return this->Map_Width; }
    int getMapHeight() const { return this->Map_Height; }
    std::vector<int> get_supportItem_pos() { return this->supportItem_pos; }
    void pop() { this->supportItem_pos.pop_back(); }

protected:
    std::vector<std::shared_ptr<Sprite2D>> Block;
    std::vector<std::shared_ptr<Sprite2D>> Decor;
    SDL_Surface* Map_Sheet;
    std::shared_ptr<Sprite2D> background;
    std::shared_ptr<Sprite2D> castle;
    std::shared_ptr<Sprite2D> flag;
    int Num_Block;
    int Num_Decor;
    std::vector<int> supportItem_pos;
    int Map_Width, Map_Height;
    int victory_w, victory_h;
    int** info;
    int* decor_width;
    int* decor_height;
    int numCoin, numGem;
};

Uint32 getpixel(SDL_Surface* surface, int x, int y);