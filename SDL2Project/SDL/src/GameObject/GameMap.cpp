#include "GameMap.h"

GameMap::GameMap() {
    Map_Sheet = NULL;
    background = NULL;
    flag = NULL;
    castle = NULL;
    Block.clear();
    Decor.clear();

    info = NULL;
    decor_width = NULL;
    decor_height = NULL;

    victory_w = 1300;
    victory_h = 0;
}

GameMap::~GameMap() {
    SDL_FreeSurface(Map_Sheet);
    Map_Sheet = NULL;

    background = NULL;

    flag = NULL;

    castle = NULL;

    delete(decor_height);
    delete(decor_width);
    delete(info);

    decor_height = NULL;
    decor_width = NULL;
    info = NULL;
}

Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16*)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32*)p;
        break;

    default:
        return 0;
    }
}

bool GameMap::loadMap(std::string path, int level) {
    std::ifstream file_map((path + "/level_" + int2str(level) + "/map_info.txt").c_str());

    file_map >> Map_Width;
    file_map >> Map_Height;
    file_map >> Num_Block;
    file_map >> Num_Decor;
    decor_height = new int[Num_Decor];
    decor_width = new int[Num_Decor];
    for (int i = 0; i < Num_Decor; i++)
    {
        file_map >> decor_width[i] >> decor_height[i];
    }

    file_map.close();

    info = new int* [Map_Height];

    for (int i = 0; i < Map_Height; i++)
        info[i] = new int[Map_Width];

    Map_Sheet = IMG_Load((path + "/level_" + int2str(level) + "/level.png").c_str());


    auto texture = ResourceManagers::GetInstance()->GetTexture("img/level_" + int2str(level) + "/background.png");
    background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);

    texture = ResourceManagers::GetInstance()->GetTexture("img/castle.png");
    castle = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);

    texture = ResourceManagers::GetInstance()->GetTexture("img/flag.png");
    flag = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);

    for (int i = 0; i < Num_Block; i++) {

        texture = ResourceManagers::GetInstance()->GetTexture("img/level_" + int2str(level) + "/block_" + int2str(i) + ".png");
        std::shared_ptr<Sprite2D> obj = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
        Block.push_back(obj);
    }

    for (int i = 0; i < Num_Decor; i++) {

        texture = ResourceManagers::GetInstance()->GetTexture("img/level_" + int2str(level) + "/decor_" + int2str(i) + ".png");
        std::shared_ptr<Sprite2D> obj = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
        Decor.push_back(obj);
    }

    SDL_Color rgb;
    Uint32 data;

    int lp_x;

    for (int i = 0; i < Map_Height; i++)
        for (int j = 0; j < Map_Width; j++)
        {
            data = getpixel(Map_Sheet, j, i);
            SDL_GetRGB(data, Map_Sheet->format, &rgb.r, &rgb.g, &rgb.b);

            if (rgb == white || rgb == green) info[i][j] = 1;
            else
            {
                info[i][j] = 0;
                if (level < numLevel)
                {
                    if (rgb == yellow) lp_x = j * TILE_SIZE + 11 * TILE_SIZE;
                    if (rgb == pink)
                    {
                        victory_w = j * TILE_SIZE;
                        victory_h = (i + 4) * TILE_SIZE;
                    }
                }
            }
        }

    std::ifstream file((path + "/level_" + int2str(level) + "/lp_pos.txt").c_str());
    int num_lp;
    file >> num_lp;

    for (int i = 0; i < num_lp; i++)
    {
        int temp_pos;
        file >> temp_pos;
        lp_pos.push_back(temp_pos);
    }
    file.close();
    std::sort(lp_pos.begin(), lp_pos.end(), std::greater<int>());

    if (level < numLevel)
        lp_pos.push_back(lp_x);

    return Map_Sheet != NULL && background != NULL;
}

void GameMap::render(int view, bool map_cleared, bool isBossLevel) {
    background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
    background->Set2DPosition(0, 0);
    background->Draw(renderer);

    SDL_Color rgb;
    Uint32 data;

    int numGrass = 0;
    int pos_x = 0, pos_y = 0;
    int height = TILE_SIZE, width = TILE_SIZE;

    if (!isBossLevel)
    {
        if (map_cleared == false)
            for (int i = 0; i <= victory_h / TILE_SIZE; i++)
            {
                info[i][victory_w / TILE_SIZE - 1] = 1;
                pos_x = victory_w - TILE_SIZE - view;
                pos_y = i * TILE_SIZE;
                Block[Num_Block - 1]->SetSize(width, height);
                Block[Num_Block - 1]->Set2DPosition(pos_x, pos_y);
                Block[Num_Block - 1]->Draw(renderer);
            }
        else
            for (int i = 0; i <= victory_h / TILE_SIZE; i++)
            {
                info[i][victory_w / TILE_SIZE - 1] = 0;
            }
    }

    for (int i = 0; i < Map_Height; i++)
        for (int j = 0; j < Map_Width; j++)
        {
            data = getpixel(Map_Sheet, j, i);
            SDL_GetRGB(data, Map_Sheet->format, &rgb.r, &rgb.g, &rgb.b);

            pos_x = j * TILE_SIZE - view;
            pos_y = i * TILE_SIZE;

            if (rgb == white) {
                width = TILE_SIZE;
                height = TILE_SIZE;
                Block[Num_Block - 1]->SetSize(width, height);
                Block[Num_Block - 1]->Set2DPosition(pos_x, pos_y);
                Block[Num_Block - 1]->Draw(renderer);
            }
            else if (rgb == green) {
                width = TILE_SIZE;
                height = TILE_SIZE;
                numGrass++;
                Block[numGrass % (Num_Block - 1)]->SetSize(width, height);
                Block[numGrass % (Num_Block - 1)]->Set2DPosition(pos_x, pos_y);
                Block[numGrass % (Num_Block - 1)]->Draw(renderer);
            }
            else if (rgb == blue) {
                width = decor_width[0] * TILE_SIZE;
                height = decor_height[0] * TILE_SIZE;
                Decor[0]->SetSize(width, height);
                Decor[0]->Set2DPosition(pos_x, pos_y);
                Decor[0]->Draw(renderer);
            }
            else if (rgb == red) {
                width = decor_width[1] * TILE_SIZE;
                height = decor_height[1] * TILE_SIZE;
                Decor[1]->SetSize(width, height);
                Decor[1]->Set2DPosition(pos_x, pos_y);
                Decor[1]->Draw(renderer);
            }
            else if (rgb == cyan) {
                width = decor_width[2] * TILE_SIZE;
                height = decor_height[2] * TILE_SIZE;
                Decor[2]->SetSize(width, height);
                Decor[2]->Set2DPosition(pos_x, pos_y);
                Decor[2]->Draw(renderer);
            }
            else if (rgb == yellow) {
                width = 23 * TILE_SIZE;
                height = 18 * TILE_SIZE;
                castle->SetSize(width, height);
                castle->Set2DPosition(pos_x, pos_y);
                castle->Draw(renderer);
            }
            else if (rgb == pink) {
                width = 2 * TILE_SIZE;
                height = 5 * TILE_SIZE;
                flag->SetSize(width, height);
                flag->Set2DPosition(pos_x, pos_y);
                flag->Draw(renderer);
            }
        }
}