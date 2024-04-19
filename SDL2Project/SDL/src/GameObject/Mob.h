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
	bool loadMob(std::string path, SDL_Renderer* renderer);
    void show(SDL_Renderer* renderer, int view);
    void drawIdle(SDL_Renderer* renderer, int view);
    void drawAttack(SDL_Renderer* renderer, int view);
    void drawMove(SDL_Renderer* renderer, int view);
    void collisionX(GameMap* MAP);
    void collisionY(GameMap* MAP);
    void update(GameMap* MAP, std::vector<Projectile>& vProjectile, Character* character, std::vector<Explosion>& vExplosion, Sound* audio);
    void setType(int type) { this->type = type; }
    void setWeapon(int weapon) { this->weapon = weapon; }
    void setRange(int minX, int maxX) { this->minX = minX; this->maxX = maxX; }
    //void spawnItem(std::vector<Item>& vItem);

    int getId() const { return this->mobId; }
    void setId(int mobId) { this->mobId = mobId; }

    pii getAttackBar() { return { nextAttack, framePerAttack }; }
protected:
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
    pii _idle;
    pii _attack;
    pii _move;
    int maxX, minX;
    int itemDrop[3];
    int prSpeed;
    int prRadius;
    int laserTick;
    bool inFollowRange;
};