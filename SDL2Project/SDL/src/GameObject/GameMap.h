#pragma once
#include "Define.h"

#include "Renderer.h"
#include "Sprite2D.h"
#include "ResourceManagers.h"

class GameMap {
public:
    GameMap();
    ~GameMap();
    bool loadMap(std::string path, int level);
    void render(int view, bool map_cleared, bool isBossLevel);
    void setNumBlock(int Num_Block) { this->Num_Block = Num_Block; }
    int getNumBlock() { return this->Num_Block; }
    void setNumDecor(int Num_Decor) { this->Num_Decor = Num_Decor; }
    int getNumDecor() { return this->Num_Decor; }

    void setNumCoin(int numCoin) { this->numCoin = numCoin; }
    int getNumCoin() { return this->numCoin; }

    void setNumGem(int numGem) { this->numGem = numGem; }
    int getNumGem() { return this->numGem; }

    int** getInfo() { return this->info; }
    int getVictory() { return this->victory_w; }
    int getMapWidth() { return this->Map_Width; }
    int getMapHeight() { return this->Map_Height; }
    std::vector<int> get_lp_pos() { return this->lp_pos; }
    void pop() { this->lp_pos.pop_back(); }

protected:
    SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();
    std::vector<std::shared_ptr<Sprite2D>> Block;
    std::vector<std::shared_ptr<Sprite2D>> Decor;
    SDL_Surface* Map_Sheet;
    std::shared_ptr<Sprite2D> background;
    std::shared_ptr<Sprite2D> castle;
    std::shared_ptr<Sprite2D> flag;
    int Num_Block;
    int Num_Decor;
    std::vector<int> lp_pos;
    int Map_Width, Map_Height;
    int victory_w, victory_h;
    int** info;
    int* decor_width;
    int* decor_height;
    int numCoin, numGem;
};

Uint32 getpixel(SDL_Surface* surface, int x, int y);