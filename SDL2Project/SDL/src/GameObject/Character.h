#pragma once
#include "GameObject.h"
#include "Define.h"
#include "GameMap.h"
#include "Projectile.h"
#include "Sound.h"

class Character : public GameObject
{
public:
    Character();
    ~Character();
    void show(SDL_Renderer* renderer, int view);
    void handleInput(SDL_Event event);
    bool loadCharacter(std::string path, SDL_Renderer* renderer, int _id);
    void Update(GameMap* MAP, std::vector<std::pair<SDL_Rect, int> >& rectMob, std::vector<Projectile>& vProjectile, Sound* audio);
    void collisionX(GameMap* MAP);
    void collisionY(GameMap* MAP);
    void drawIdle(SDL_Renderer* renderer, int view);
    void drawMove(SDL_Renderer* renderer, int view);
    void drawAttack(SDL_Renderer* renderer, int view);
    void drawDied(SDL_Renderer* renderer, int view);
    void drawVictory(SDL_Renderer* renderer, int view);
    void setStatus(int status) { this->nStatus = status; }
    void setFrame(int frame) { this->frame = frame; }
    int getStatus() const { return this->nStatus; }
    bool getAttack() const { return this->finishAttack; }
    int getId() const { return id; }
    pii getAttackBar() { return{ nextAttack, framePerAttack }; }
    bool startAttack() const { return nextAttack == 0; }
    bool getMove() const { return (pressed['a'] || pressed['d']); }
    bool onGround() const { return (!isFalling); }
    bool jumped() const { return pressed[' '] && isFalling == false; }
    SDL_Rect getMelee() const;
    bool meleeAttack() const { return !finishAttack && frame == frameAttack && type == TYPE::MELEE; }

protected:
    SDL_Texture* portrait;

    SDL_Texture* idleAnimation[2];
    SDL_Texture* moveAnimation[2];
    SDL_Texture* attackAnimation[2];
    SDL_Texture* diedAnimation[2];
    SDL_Texture* jumpAnimation[2];

    SDL_Texture* victoryAnimation;

    SDL_Rect melee;

    // pii: pair <int, int>
    pii _idle;
    pii _move;
    pii _attack;
    pii _died;
    pii _victory;

    int id;
    int frame;
    bool isJumping;
    bool isFalling;
    int status;
    int nStatus;
    
    enum STATUS {
        IDLE = 0,
        MOVE = 1,
        JUMP = 2,
        ATTACK = 3,
        DIED = 4,
        VICTORY = 5,
    };

    bool pressed[300] = { false };
    bool finishAttack;
    int nextAttack, framePerAttack, frameAttack;
    bool facing;
    int type;
    int idProjectile, prSpeed, prLastTime;

    enum TYPE {
        RANGED = 0,
        MELEE = 1,
    };
};