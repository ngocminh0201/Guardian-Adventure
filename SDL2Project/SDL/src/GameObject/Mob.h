#pragma once
#include "Define.h"
#include "GameObject.h"
#include "GameMap.h"
#include "Character.h"
#include "Sound.h"
#include "Projectile.h"

class Mob : public GameObject {
public:
	Mob();
	~Mob();
	bool loadMob(std::string path);
    void show(int view);
    void drawIdle(int view);
    void drawAttack(int view);
    void drawMove(int view);
    void collisionX(GameMap* MAP);
    void collisionY(GameMap* MAP);
    void tick(GameMap* MAP, std::vector<Projectile>& vProjectile, Character* character, std::vector<Explosion>& vExplosion, Sound* audio);
    void setType(int _type);
    void setWeapon(int _type);
    void setRange(int l, int r);
    //void spawnItem(std::vector<Item>& vItem);

    int getId();
    void setId(int _id);

    std::pair<int, int> getAttackBar();
protected:
    SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();
    //std::shared_ptr<SpriteAnimation> animation;
    //std::vector<std::shared_ptr<SpriteAnimation>> idleAnimation;
    //std::vector<std::shared_ptr<SpriteAnimation>> attackAnimation;
    //std::vector<std::shared_ptr<SpriteAnimation>> moveAnimation;
    SDL_Texture* idleAnimation[2];
    SDL_Texture* attackAnimation[2];
    SDL_Texture* moveAnimation[2];
    SDL_Texture* laser;
    SDL_Rect melee;
    int frameAttack;
    bool hostile;
    int idProjectile;
    int type;
    enum TYPE {
        RANGED = 0,
        MELEE = 1,
        THROW = 2,
        LASER = 3,
        BOMB = 4,
        FOLLOW = 5,
    };
    int weapon;
    bool idle, move, attack;
    int frame;
    int nextAttack;
    int framePerAttack;
    int mobId;
    bool facing, direction;
    std::pair<int, int> _idle;
    std::pair<int, int> _attack;
    std::pair<int, int> _move;
    int maxX, minX;
    int itemDrop[3];
    int prSpeed;
    int prRadius;
    int laserTick;
    bool inFollowRange;
};